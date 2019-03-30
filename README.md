# CommeCOM
Header-only library providing basic means for working with "comme" (like) COM objects for all platforms.

## Status
The library is currently experimental. There are still bugs lurking and waiting to strike when you expect it less.

## Usage
The primary usa-case of the library is for querying interfaces and acccessing functionality from dynamically loaded plug-ins (DLLs or shared objects) while maintaining the binary compatibilty accross compilers and compiler versions.

### Prerequisites
The only prerequisite is a C++ compiler with support for ```c++11```.

### Defining an interface
To define an interface, there is really nothing special exceping the fact that the interface must inherit from ```IUnknown``` (otherwise cannot be used for implementing COM objects). In the example below we define an interface ```IDrawable``` which defines a single method ```draw ()```.

```
struct IDrawable : public IUnknown
{
  virtual void draw () noexcept = 0;
};
```

Ok, there are a few things which require a bit of extra care.
* First of all, all the methods must be defined pure ```virtual```.
* Then, the inteface must have no ```virtual``` destructor (actually no destructor at all).
* Third, because of the point above, the interface must not have data members.
* Finally, all interface methods must be declared ```noexcept```.

The last requirement comes from the fact that in the primary use-case (of dynamically loaded plug-ins) and in the context of binary compatibility we cannot propagate exceptions beyond the DLL boundary. If there is no such constraint, methods can also throw exceptions and the last requirement is void.

It looks like a lot of requirements, but let's not forget that we just want to define a pure abstract interface here (therefore no data members and no destructor are reasonable).

#### Making the interface unique

Next, we need to make sure that we can uniquely identify and reffer to the newly created interface. We will assing an unique UUID (```GUID```) to the interface. We call this unique GUID an interface ID or ```IID```. 

The library defines a ```GUID``` as follows:
```
struct GUID
{
  uint32_t data1;
  uint16_t data2;
  uint16_t data3;
  uint8_t  data4[8];
};

```

The ```IID``` is used for querying interfaces.

To assign such a ```GUID``` to an interface, one of the following several ways can be used.

##### 1. Defining an ```IID``` using the classical method
The simplest method of defining an ```IID``` is by defining a symbol with a suitable name which holds the ```GUID``` value.

```
extern "C" const GUID IID_IDrawable = { 0x12345678, 0xabcd, 0xef01, { 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01 } };
```

The ```extern "C"``` part is critical to prevent mangling of the name of our interface ```IID``` identifier. It is recommended to use the same naming scheme for all inteface IDs (```IID_IMyInterface```) for consistenty.

##### 2. Defining an ```IID``` using ```IID_Traits```
This method is required when using the library provided facilities for querying interfaces. The library provides an interface trait called ```IID_Traits``` which maps interface types to ```GUIDs```.


To define an ```IID``` for an already existing interface, just provide a specialization of the trait for the interface with a ```static``` member with the name ```iid```, as follows.

```
template <>
struct IID_Traits <IDrawable>
{
  static const GUID iid;
}

const GUID IID_Traits <IDrawable>::iid = { 0x12345678, 0xabcd, 0xef01, { 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01 } };
```

##### 3. Defining an ```IID``` using the library facility (recommended)
Finally, the safest way to define a new ```IID``` is to use the library provided macro ```CCOM_DEFINE_IID``` which defines the ```IID``` in both ways from above (i.e. provides the classical extern symbol for raw querying as well as the trait for the library internal workings).

An example is below.

```
CCOM_DEFINE_IID (IDrawable, 0xAB00CD00, 0x1234, 0x4568, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
```

#### Beware of symbol redefinition errors
You are most likely to define ```IIDs``` in header files which can be potentially included in more than one source file which in turn can be linked to the same executable. Having the same symbol defined in multiple object files linked to the same executable leads to linker errors. To avoid this, the defaul behaviour of ```CCOM_DEFINE_IID``` is to just declare the respective ```IID``` but not define it. To actually define it you must provide the following definition before the actual macro.

```
#define CCOM_INSTANTIATE_IID
```

This way you can control where and when are the ```IIDs``` defined to avoid linker errors.

### Providing an implementation
After defining an abstract interface, we must provide at least one implementation. Classically, that means defining a class which implements (inherits) the interface and overrides all the virtual methods. An example is provided below.

```
class CPaper : public IDrawable
{
public:
  // Methods inherited from IUnknown
  virtual RESULT queryInterface (RefIID iid, void **ppvInterface) noexcept override;
  virtual uint32_t addRef () noexcept override;
  virtual uint32_t release () noexcept override;

public:
  // Methods inherited from IDrawable
  virtual void draw () noexcept override;
};
```

Also, implementations must be provided for all methods in the example above.

However, the since the first three methods (inherited from ```IUnknown```) are not related to the actual functionality provided by the implementation, the library provides a way to "hide" them. Instead of inheriting directly from ```IDrawable```, you can inherit from ```CComObjectBase``` which is a class template implementing the three methods inherited from IUnknown and also inheriting from all interfaces provided as templates.

A simple usage is shown below (equivalent to the example above).
```
class CPaper : public CComObjectBase <CPaper, IDrawable>
{
public:
  virtual void draw() noexcept override;
};
```

Now, only the ```draw ()``` method needs implementation. Note that in the template instantiation of the ```CComObjectBase``` class we also specified the final class ```CPaper```. This is required because the ```release``` method must know the final object type in order to properly deconstruct the object when the reference count for that particular object reaches zero.

The ```CComObjectBase``` class can be used with multiple interfaces as follows:
```
class CPaper : public CComObjectBase <CPaper, IDrawable, IFoldable, IRippable>
```
In fact, you can supply as many interfaces as you wish, with the only requirement that the first template argument is the final type of the object (see [CRTP](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)).

### TODO - more to come