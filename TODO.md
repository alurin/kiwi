TODO
====
[ ] Clean up all source code
    [ ] Syntax nodes
        [ ] Rename `ExpressionNode` to `ExpressionStatementNode`
        [ ] Rename `LeftNode` to `MutableNode`
        [ ] Rename `RightNode` to `ExpressionNode`
    [ ] Types
        [ ] Devide types to:
            * Value types: `integer`, `char` and `float`
            * Structure types: `string`, `structure`, `arrays`
            * Object types: `objects`
        [ ] Add support for interfaces
        [ ] Add support for visibility:
            [ ] Field visibility
                * `private`
                * `protected`
                * `public`, this case expanded to property
            [ ] Method visibility
                * `private`   - inlined
                * `internal`  - visible in all internal module's classes, inlined
                * `protected`
                * `protected internal` - visible in all internal module's classes, but only in child external classes
                * `public`