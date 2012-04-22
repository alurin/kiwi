TODO
====

Source code clean up
--------------------
* Types
    * Devide types to:
        * Value types: `integer`, `char`, `float` and `structures`
        * Small object types: `string`, `arrays`
        * Full object types: `objects`
* Move all LLVM code from syntax nodes and metadata
* Warning and errors

Runtime
-------
* Add support for return pointer for methods or operators

Features
--------
* Add support for inheritance (multi)
* Add support for method overrides by virtual tables
* Add support for interfaces
* Add support for properties (C# style or PHP style)
* Add support for visibility:
    * Field visibility
        * `private`
        * `protected`
        * `public`, this case expanded to property
    * Method visibility
        * `private`   - inlined
        * `internal`  - visible in all internal module's classes, inlined
        * `protected`
        * `protected internal` - visible in all internal module's classes, but only in child external classes
        * `public`