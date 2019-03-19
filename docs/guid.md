---
title: IIDs and GUIDs
---

# IIDs and GUIDs
To overcome different mangling imposed by different compilers (or even compiler versions), we refer to our interface using UUIDs / GUIDs, which we will call Interface IDs (IIDs). The library defines such a GUID as follows:
```c++
struct GUID
{
  uint32_t data1;
  uint16_t data2;
  uint16_t data3;
  uint8_t  data4[8];
};
```
Each interface will be associated with an unique GUID, refered to as the IID of the interface. 
## IID definition
The simplest and most straight forward way to define an IID is to define a symbol, unually named ```IID_InterfaceName``` where ```InterfaceName``` is just the name of the interface in source code. The symbol is of type ```GUID``` and can be defined as follows:
```c++
extern "C" const CCom::GUID IID_IDrawable = { 0x11223344, 0x5566, 0x7788, { 0x99, 0x00, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF }};
```
The ```extern "C"``` part is important because we need to make sure that this symbol has the same name regardless of the compiler mangling. Since this symbol is defined in a header file alongside the interface definition itself, it will be distributed to all clients, as well as implementers of our interface. Assuming that all will use the same compiler or even compiler version is plain wrong, therefore we have to use the ```extern "C"``` language feature to set a common ground for all.

## ```fromStr``` - converting from string representation to GUIDs
Another way to define the ```IID_``` symbols is by using a string representation of GUIDs instead of the binary one. The library provides an inline free function - ```fromStr``` - which converts GUIDs from string representation to binary representation. ```fromStr``` is declared as follows:
```c++
inline constexpr GUID fromStr (const char * const p);
```
The only argument is the string representation of a GUID. Valid GUID string representations (accepted by the library) are the following:
* ```"11223344556677889900AABBCCDDEEFF"```
* ```"{11223344556677889900AABBCCDDEEFF"```
* ```"11223344-5566-7788-9900-AABBCCDDEEFF"```
* ```"{11223344-5566-7788-9900-AABBCCDDEEFF}"```
* In fact, the library accepts any form of GUID representations (in terms of hyphen placement), but please don't abuse it.

```fromStr``` is implemented such that its return value can be completely evaluated at compile time. The above definition of ```IID_IDrawable``` can now be updated to this:
```c++
extern "C" const CCom::GUID IID_IDrawable = CCom::fromStr ("{11223344556677889900AABBCCDDEEFF}");
```

## ```IID_Traits```
While the COM technology makes exlcusive use of the IIDs as defined earlier, CommeCOM (as many other modern libraries) plays a trick by defining a special type trait (```IID_Traits```) which is used to map real types such as the interface ```IDrawable``` to GUID objects. The interface trait is defined as follows:
```c++
template <class I>
struct IID_Traits
{
  inline static const GUID iid ();
};
```
By specializing ```IID_Traits``` for a particular interface type, we effectively provide an easy and safe way to map the respective IID and bind it into all places in code where it is required. Such a specialization for ```IDrawable``` looks similar to this:
```c++
template <>
struct IID_Traits <IDrawable>
{
  inline static const GUID iid ()
  {
    // return { 0x11223344, 0x5566, 0x7788, { 0x99, 0x00, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF }};
    // To ensure compatibility with other versions of COM, use previously defined IID symbol.
    return IID_IDrawable;
  }
};
```
It is always good practice to ensure compatibility with other implementations of COM, therefore the safest specializations will return the previously defined global symbol ``IID_```.
## ```CCOM_DEFINE_IID``` and ```CCOM_DEFINE_IID_NS```

Using the ```CCOM_DEFINE_IID``` and ```CCOM_DEFINE_IID_NS``` macros, we can easily define and bind IIDs. Both macros must be used in the global namespace. While ```CCOM_DEFINE_IID``` defines IIDs for interfaces declared in the global namespace, ```CCOM_DEFINE_IID_NS``` defines IIDs for interfaces defined in named namespaces.

### Define IIDs for interfaces in the global namespace
The ```CCOM_DEFINE_IID``` macro can be used to define and bind IIDs to interfaces defined in the global namespace. Its usage is as follows:
```
CCOM_DEFINE_IID (interface name, const char array representing a GUID);
```

### Define IIDs for interfaces in named namespaces
If your interface is defined in a named namespace (and it should be), they you might want to use the ```CCOM_DEFINE_IID_NS``` macro. It behaves the same way as ```CCOM_DEFINE_IID```, but accepts an extra first parameter, the namespace of your interface.
```
CCOM_DEFINE_IID_NS (namespace, interface name, const char array representing a GUID);
```

The above example can be simplified using, for example, ```CCOM_DEFINE_IID``` as follows:
```c++
CCOM_DEFINE_IID (IDrawable, "11223344556677889900AABBCCDDEEFF");
```