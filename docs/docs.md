---
title: Documentation
---

# Documentation
Detailed information about prerequisites, installation, usage and the limitations of the library is given here.

## Dependencies
The library depends on features provided by the ```c++11``` standard, therefore you must use it with a C++ compiler which supports at least that. In particular, make sure that your compiler supports variadic templates, as the library makes heavy use of them.

Included with the library headers, the Git repository also provides several examples. Compiling the examples has additional requirements:
* libboost1.61 or above (needed for Boost.DLL)


## Installation
CommeCOM is a header-only library. To install it, download the latest release (or clone the Git repository for the most up-to-date development code) and extract it at a convenient location into your system. An example of installing into the usual /usr/include is given below.

```
$ # TODO 
```

## Defining an interface
The heart of interface programming is defining good interfaces. An interface is, from our C++ perspective, just an abstract class consisting only of pure virtual methods and no data members. Let's consider the following interface providing one method, ```draw```, as our example:
```
struct IDrawable
{
  virtual void draw () = 0;
};
```
Considering our primary use-case, this inteface sits between two separate modules: one client requiring the interface and one plug-in providing it. Moreover, the "communication" or data exchange between the client and the plug-in is done at binary level (by function calls directly from the client to the plug-in). Although it is fairly easy to guarantee the binary compatibility of the client with the plug-in and vice-versa (for example by enforcing strict build rules and by making sure that both are compiled in the same time, with the same compiler, or by limiting the number of users and use-cases), this is not an assumption to make. We must proactively seek to ensure binary compatibility even in the absence of the comfort provided by our build systems and the assurances of our clients.

The solution, of course, is versioning.

**PAUSE AND PONDER ! If the above motivation does not apply to you, then you might just not need using this library or any similar. However, you might want to consider binary compatibility anyway, especially when working with two or more files interacting at binary level for which you are not the only user and / or maintainer.**

But how to version our plug-in? What is to be done if, for example, a new method needs to be provided to the users of ```IDrawable```, in addition to ```draw```? In the UNIX world, the answer is versioning numbers. We can attach a major and minor number to our plug-in and code the client to only accept certain major numbers. Any change of the minor number will represent a change into the implementation of our interface that does not break compatibility, while a change in the major number will signal to the client that the compatibility is broken.

However, sometimes the systems that we build have many many plug-ins that must work together and are not maintained by the same teams. Therefore, it might happen that a change of the major version has different meanings to different teams maintaining diferent plug-ins. We will eventually end up doing another layer of versioning and compatiility checking since we need to pair and match up versions of our plug-ins that can or cannot work together. Sometimes!

An alternative to the minor and major numbering scheme is interface (programming and) versioning. The main different is that interface versioning applies to individual interfaces as opposed to whole modules / files (possibly containing more than one interface implementations). In addition, certain interface versioning techniques, including COM, also provide binary compatibility accross compilers and compiler versions.

To benefit from interface versioning and the binary compatibity, we must modify our ```IDrawable``` interface in the following way:
* inherit it from a common base, ```IUnknown```, thus making sure that we can relate all "versions" of our interface to a common base
* provide and bind an unique identifier to our interface so we can refer to it regardless of what the compiler can and will do to its name (due to mangling).

The updated version of our interface looks like this:
```
struct IDrawable : public CCom::IUnknown
{
  virtual void draw () noexcept = 0;
};

CCOM_DEFINE_IID (IDrawable, "{11223344-5566-7788-9900-AABBCCDDEEFF}");
```

Notice that there is no virtual destructor. We don't need one. (TODO, explain why).
For more information on ```CCOM_DEFINE_IID``` please visit [IIDs and GUIDs](guid)

## Providing an implementation
Any implementation of our ```IDrawable``` interface must inherit from the interface. The simplest way to define it goes as follows:
```
class CPaper : public IDrawable
public:
  virtaul void draw () noexcept override;

[...]

public:
  virtual RESULT queryInterface (RefIID iid, void **ppvInterface) noexcept override;
  virtual uint32_t addRef () noexcept override;
  virtual uint32_t release () noexcept override;
};
```
By inheriting from ```IDrawable```, we implicitely inherit from ```IUnknown``` as well, which is important. Besides the familiar ```void draw ()``` method, we must also provide definitions (implementations) for three more methods, all part of the ```IUnknown``` interface.

The ```IUnknown``` common base interface is defined as follows:
```
struct IUnknown
{
  virtual RESULT queryInterface (RefIID iid, void **ppvInterface) noexcept = 0;
  virtual uint32_t addRef () noexcept = 0;
  virtual uint32_t release () noexcept = 0;
};
```
The purpose of ```IUnknown``` is to provide means for querying interface availability (i.e. versioning) and for managing the object's lifetime. Why? Because plug-ins (separate modules, usually DLLs or DSOs) define a fairly restrictive boundary between them and the client loading them.  It might be the case that what the client understands as the layout of a certain class is very different to what the plug-in understand. To prevent disaster, we enfore a policy where objects are created, managed and destroyed by a single party. In case the client needs to create an object, we enfore that the client needs to also manage and destroy it. Same goes for the plug-in. Therefore, the lifetime management of such "interoprable" objects is embedded within the object itself so it can somehow "travel" the plug-in barrier.