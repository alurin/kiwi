TODO
====

Git
---
Add submodule for [LLVM](git://github.com/earl/llvm-mirror.git)

**MEMORY LEAKS**
----------------
* source/kiwi-core/Lang/Factory.cpp:70
* source/kiwi-core/Lang/Factory.hpp:117

Current
-------
* Array type
* Range expression
* Vardiac params
* Boxing/Unboxing for primary types

Source code clean up
--------------------
* Add compound type for struct and object types
* Add base for interface and object type
* Add normal handle for inheritance and implements
* Subtraction and invoke operators
* Warning and errors

Runtime
-------
* Add support for return pointer for methods or operators
* Add support for GC

Features
--------
* Add support for exceptions
* Add support for GC
* Add support for inheritance (multi)
* Add support for method overrides by virtual tables
* Add support for interfaces
* Add support for properties (C# style or Ruby style)
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
* Add support for metadata attributes and metadata evalutions (e.g. methods for extend class in build time)

Question
--------
    * What I must have in language?
    * What I want to try?
    * Why should I want this?

Language
--------
    * Dynamic or static?
    * Script or compile? Hybrid, as crack?
    * Function programming? Or not?
    * Object programming:
        - Prototype or normal inheritance?
        - Multi inheritance with fields address map and methods virtual table.
        - Attributes? If yes, than not only declorative, but add imperative
        - Access level?
        - Properties, constructors, events?
        - Control for extends
        - AOP?
        - Closures and continuations?
        - Dynamic override methods and extends classes?
        - Structures and objects?
    * Runtime library:
        - Reflection
        - Event system
        - Memory management:
            - Manual memory manager
            - Simple references count and weak and strong references    (implement?)
            - Complex garbage collector                                 (prefered)
        - File system:
            - Virtual FS (prefered)
            - Normal FS

vtable: void*[]         -- dynamic array or hash table //
amap:   int[];          -- dynamic array or hash table //

metadata:
    vtable  %vtable;    -- dynamic array or hash table //
    amap    %amap       -- dynamic array or hash table //

object:
    metadata *classid;  -- fixed value
    data**              -- dynamic structure

call
    if !updated -> update
    load pointer

load:
    if !updated -> load null

store:
    if !exists && !updated -> update
    save value
