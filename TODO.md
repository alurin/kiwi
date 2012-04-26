TODO
====

Git
---
Add submodule for [LLVM](git://github.com/earl/llvm-mirror.git)

Source code clean up
--------------------
* [ ] Unary, minary, multiary and methods abstract base
    * [ ] Unified emitters
* [ ] Abstract base for Unary, minary, multiary, calls and e.t.c:
    * [ ] Unified emit methods
    * [ ] Resolve callable (e.g. find method or operator from type)
    * [ ] Types casting, if requested
* [ ] Build process
    * [ ] Create types from current file
    * [ ] Create members (methods, fields) in class from current files
    * [ ] Create IR from callables
* [ ] Array type
* [ ] Range expression
* [ ] Subtraction and invoke operators
* [ ] Clean up memory leaks!!!
* [ ] Move all LLVM code from syntax nodes and metadata
* [ ] Warning and errors
* [ ] Variable initilizator position in statement!!!

Runtime
-------
* [ ] Add support for return pointer for methods or operators
* [ ] Add support for GC

Features
--------
* [ ] Add support for exceptions
* [ ] Add support for GC
* [ ] Add support for inheritance (multi)
* [ ] Add support for method overrides by virtual tables
* [ ] Add support for interfaces
* [ ] Add support for properties (C# style or Ruby style)
* [ ] Add support for visibility:
    * [ ] Field visibility
        * [ ] `private`
        * [ ] `protected`
        * [ ] `public`, this case expanded to property
    * [ ] Method visibility
        * [ ] `private`   - inlined
        * [ ] `internal`  - visible in all internal module's classes, inlined
        * [ ] `protected`
        * [ ] `protected internal` - visible in all internal module's classes, but only in child external classes
        * [ ] `public`
* [ ] Add support for metadata attributes and metadata evalutions (e.g. methods for extend class in build time)

Question
--------
    * What I must have in language?
    * What I want to try?
    * Why should I want this?

Build configs
-------------
    * Enable debug build
    * FindICU.cmake - fing ICU libraries and headers

Engine
--------------
    * LLVM not clean up after shutdown

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

Minor
-----
    * Clean up all text files
    * Cool text for config script options
    * Enable options for module and interfaces buildings

Modules
-------
    * Change modules structure:
        - kiwi-core             Core module
        - kiwi-code-generator   Code generator based on LLVM backend
        - kiwi-runtime          Runtime module
        - kiwi-apache2-module   Apache host module
        - kiwi-console          Console host application

* English orphography!!!
