---
title: Entry points
---

# Entry points
When working with plug-ins, extra care must be taken at the plug-in barrier. Due to the uncertainty of same-compiler and same-compiler-version assumptions, we cannot guarantee that both the client and the plug-in agree on objects layout. When a client tries to create an instance of a plug-in provided class on the free store, two main actions take place:
* the allocator is invoked to allocate memory the size of the object
* the constructor is called to initialize the object

Since the constructor for the object has been generated using the plug-in compiler and the allocator is generated using the client compiler, those do not necessarily agree on the layout of the object, resulting in dissastrous consequences. Therefore, we make sure that objects are only created and destroyed by the party providing them.

In the case of our plug-in, the plug-in itself must provide means for creating and destroying objects. The lifetime, as well as destruction of COM objects is handled in the objects themselves (for more information check [CInterfacePtr](smartpointer)). However, the object creating must be handled separately. Most often the factory pattern proves suitable for our situation and it is definitely something worth considering. In our particular case, the library provides a basic method for defining simplistic "factory" methods for generating COM objects from within the plug-in.

Accessing this part of the library requies the following include:
```c++
#include <CCom/Dynamic.hpp>
```

## ```CCOM_DL_ENTRY_POINT```
The ```CCOM_DL_ENTRY_POINT``` macro can be used to define such a simplistic entry point into the plug-in for creating a certain COM object. It requires at least two parameters as follows:
```
CCOM_DL_ENTRY_POINT (symbol name for the entry point, final class of the object to be instantiated [, arguments to the constructor of the final class] );
```
In addition, it accepts a third variadic argument consisting of a list of parameters to be passed to the constructor of the final class to be created within the respective entry point.

An example usage of the macro:
```c++
CCOM_DL_ENTRY_POINT (getInstance, CPaper);
```
This line will generate a function called ```getInstance``` which can be used as entry point into the plug-in, for creating objects of type ```CPaper```. The signature of the function is:
```c++
extern "C" CCom::RESULT getInstance (CCom::RefIID iid, void **ppvInterface);
```

As you can see, the entry point does not depend on any of the interfaces or implementations. Instead, it returns the result (the newly created object) through the second parameter - an opaque pointer. For convenience in use, the same generic signature is defined as a type:
```c++
using DLEntryPointPPVFunc = RESULT(RefIID iid, void **ppvInterface);
```

Moreover, the entry point is defined as ```extern "C"``` to prevent mangling and ensure that the name is visible as-is regardless of compiler or compiler version.

## ```getInterfacePtr```
Once the entry point is defined on the plug-in side, it can be accessed on the client side. In the case of DLLs and DSOs, the plug-in is dynamically specified and loaded and the symbol is searched with facilities such as ```dlopen``` and ```dlsym```. A more straightforward way is by suing ```Boost.DLL``` or a similar wrapper over the DLL handling primitves. An example using ```Boost.DLL``` goes as follows:
```c++
namespace dll = boost::dll;

dll::shared_library impl ("libmyplugin.so");
auto pfnGetInterface = impl.get <CCom::DLEntryPointPPVFunc> ("getInstance");
```

Here, we load the plugin ```libmyplugin.so``` and search for the ```getInstance``` symbol previously defined using ```CCOM_DL_ENTRY_POINT```.

Once we have the symbol, we can use ```getInterfacePtr``` to acquire a smart pointer over the raw interface pointer, automatically managing the lifetime of the object. For more information on ```CInterfacePtr``` and COM object management, check [CInterfacePtr](smartpointer).

Continuing the previous example, we can now obtain a pointer to our desired interface (e.g. ```IDrawable```, provided by ```CPaper```) as follows:
```c++
CCom::CInterfacePtr <IDrawable> pDrawable;
CCom::getInterfacePtr (pfnGetInterface, pDrawable);

// [...]

pDrawable->draw ();
```

```getInterfacePtr``` is a helper function which takes two parameters:
* a pointer to a function, pointing to the entry point symbol (in our case ```getInstance```), defined in the plug-in
* a reference to an instance of ```CInterfacePtr``` to which the new raw pointer will be attached (the old interface pointer managed by the instance of ```CInterfacePtr``` will be released if the call to ```getInterfacePtr``` succeeds).

```getInterfacePtr``` will call the entry point and will query the desired interface (specified as the ```CInterfacePtr``` template argument). Upon success, the function will return ```S_OK``` and will attach the raw interface pointer to the instance of ```CInterfacePtr```, otherwise an error code will be returned (```E_NOINTERFACE``` in case of query failure or other code in case of other type of error) and the smart pointer instance will not be touched.