Object structure
================

* **vtable**      = array of int8*                          /// -- vector                   ## pointers to functions
* **amap**        = array of int32                          /// -- vector                   ## offset of fields
* **data**        = struct of uint32, ...                   /// -- structure                ## attributes storage
                                                        ///    1. Count of fields
* **vmeta**       = vtable*                                 /// -- global variable          ## virtual table
* **ameta**       = amap*                                   /// -- global variable          ## address map
* **dmeta**       = struct of type*, data*                  /// -- struct for allocate      ## metadata storage
* **object**      = struct of vmeta*, ameta*, dmeta*        /// -- struct for instructions  ## object storage

Object operations
=================

Create
------
* Allocate `data`                                               [LLVM+GC]
* Call initilizators for data                                   [LLVM]
* Allocate `dmeta`                                              [LLVM+GC]
* Add finalizator for `dmeta`                                   [LLVM+GC]
* Store pointer to data in dmeta                                [LLVM]
* Allocate `object` in stack                                    [LLVM]
* Store `vmeta`, `ameta` and `dmeta` object                     [LLVM]
* Call constructors for object                                  [LLVM]
* Return result                                                 [LLVM]

Load
----
* Find offset by index                                          [LLVM]
* Calculate actual offset in object->dmeta->data                [LLVM]
* Load by offset                                                [LLVM]

Store
-----
* If index is greater than current count of fields              [LLVM+runtime]
    resize (create new `data` structure and copy values
    from old `data` structure)
* Find offset by index                                          [LLVM]
* Store value by offset                                         [LLVM]
* Return result                                                 [LLVM]

Call
----
* Find pointer by index                                         [LLVM]
* Cast pointer to actual function                               [LLVM]
* Call function                                                 [LLVM]
* Return result                                                 [LLVM]
