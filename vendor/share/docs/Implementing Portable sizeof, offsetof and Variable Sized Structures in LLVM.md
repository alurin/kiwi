Implementing Portable sizeof, offsetof and Variable Sized Structures in LLVM
============================================================================

June 24, 2005 - Initial Revision
--------------------------------

This note describes how an LLVM language front-end can generate portable code
when the sizes of a type or the offset of a field in a structure are needed.
These sizes and offsets are target-specific, and can depend on the alignment,
structure padding and pointer size used by a target.  It is often useful to be
able to defer evaluation of these values until code generation time, for use
when generating LLVM code that is intended to be portable to multiple targets.

To illustrate these concepts, we show how they can be used to implement
efficient variable sized arrays in LLVM (e.g. as used for 'pascal strings').

Using getelementptr for sizeof and offsetof
-------------------------------------------

Though LLVM does not contain a special purpose sizeof/offsetof instruction, the
getelementptr instruction can be used to evaluate these values.  The basic idea
is to use getelementptr from the null pointer to compute the value as desired.
Because getelementptr produces the value as a pointer, the result is casted to
an integer before use.

For example, to get the size of some type, %T, we would use something like
this:

  %Size = getelementptr %T* null, int 1
  %SizeI = cast %T* %Size to uint

This code is effectively pretending that there is an array of T elements,
starting at the null pointer.  This gets a pointer to the 2nd T element
(element #1) in the array and treats it as an integer.  This computes the
size of one T element.

To get the offset of some field in a structure, a similar trick is used.  For
example, to get the address of the 2nd element (element #1) of { sbyte, int* }
(which depends on the target alignment requirement for pointers), something
like this should be used:

  %Offset = getelementptr {sbyte,int*}* null, int 0, uint 1
  %OffsetI = cast int** %Offset to uint

This works the same way as the sizeof trick: we pretend there is an instance of
the type at the null pointer and get the address of the field we are interested
in.  This address is the offset of the field.

Note that in both of these cases, the expression will be evaluated to a
constant at code generation time, so there is no runtime overhead to using this
technique.

Using sizeof/offsetof to allocate memory & variable sized structures
--------------------------------------------------------------------

One time that these techniques are useful is when allocating memory for a
structure with malloc or a garbage collector.  These routines need to know the
actual size of an object.  This is complicated by the fact that some langauges
allow for variable sized structures: structures which end with an array whose
length is determined at allocation time.  This sort of construct is used for
many sorts of language constructs and some languages even allow programmers to
write these explicitly (e.g. C99).

LLVM explicitly supports variable sized arrays through the use of zero length
arrays.  For example, the structure type "{ uint, [0 x float] }" can be used to
define an array of floats of variable size.  Presumably the actual number of
elements is stored in the initial uint element.

In order to dynamically allocate an instance of this data type, code the the
following can be used (which uses the offsetof technique described above):

%array = type { uint, [0 x float] }
implementation
%array *%NewArray(uint %Length) {
  ;; Get the offset of the 'Length' element of the array from the null
  ;; pointer.
  %Size = getelementptr %array* null, int 0, uint 1, uint %Length
  %SizeU = cast float* %Size to uint
  %Ptr = malloc sbyte, uint %SizeU
  %Result = cast sbyte* %Ptr to %array*

  ;; Remember the allocated length for later use.
  %SizePtr = getelementptr %array* %Result, int 0, uint 0
  store uint %Length, uint* %SizePtr
  ret %array* %Result
}

There are many other potential uses of these techniques.
