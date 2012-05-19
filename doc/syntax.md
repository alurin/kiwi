Syntax and symantic
===================
Kiwi is OOP language, currently supported:
* TODO

Primary types
=============
Kiwi used this primary types:
* **int**               - 32 bit signed integers (4 byte)
* **bool**              - Logical type with two value: `true` and `false` (size unknown, 1 or 8 bit)
* **char**              - Character in Unicode-16 encoding (16-bit)
* **string**            - String containets with Unicode-16 encoding characters and length

Variables
=========
All variables has type and name begin with `$`([a-zA-Z][a-zA-Z0-9]) e.g:

    int $v;
    string $b;

All variable can have initilizator:

    int $a = 10;
    string $b = "This is string";

If type of result for expression or call is unknown, you can use virtual type `auto` for variable:

    auto $a = 10;                   // This type is `int`
    auto $b = "This is string";     // This type is `string`
