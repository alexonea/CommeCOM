---
title: CInterfacePtr
---

# CInterfacePtr
```CInterfacePtr``` is an intrusive smart pointer aiming to provide lifetime management for COM objects. It does so by automatically calling ```addRef``` and ```release``` on the contained raw interface pointer in a RAII fashion.

Accesing this part of the library requies the following include:
```c++
#include <CCom/CInterfacePtr.hpp>
```

## ```interface_cast```
Navigating through the interfaces and interface versions is done using ```queryInterface```.  While ```CInterfacePtr``` provides a method ```queryInterface``` to assist the navigation in case of its use, the library allows for explicit "casts" between ```CInterfacePtr``` instances using ```interface_cast```.

An example a the simplest usage:
```c++
// Initialize pDrawable to a valid raw interface pointer (or aquire it using a different but valid method)
CCom::CInterfacePtr <IDrawable> pDrawable (...);

// [...]

// Create an empty instance of CInterfacePtr for IFoldable
CCom::CInterfacePtr <IFoldable> pFoldable;

// Try to "cast" pDrawable to pFoldable (calling queryInterface in the process)
pFoldable = CCom::interface_cast <IFoldable> (pDrawable);
```

Note, the cast can be done in a single line as follows:
```c++
auto pFoldable = CCom::interface_cast <IFoldable> (pDrawable);
```

Checking whether the cast was successful is done using the ```bool ()``` operator provided by ```CInterfacePtr```:
```c++
if (pFoldable)
  // do something with pFoldable
else
  // error, does not point to an implementation of IFoldabe
```