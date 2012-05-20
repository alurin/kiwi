Change log
==========

05/20/2012 Kiwi 0.1
-------------------
* Initial version
* Simple support for unicode strings
* Support for compound types (object classes):
    * Class as set of fields and methods, it's standart :)
    * Multi inheritance, with single dynamic dispatch for methods and address map for fields
    * Method overloading and overriding
    * Simple conflict resolution: first method or field is god.
* Primary types:
    * 32 bit integer
    * Unicode character
    * Boolean (logical) type
* External interface almost pure from the use of LLVM

Note: Сurrent implementation of objects havy expects information from the runtime (JIT)
