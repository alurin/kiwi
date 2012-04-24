Unicode Flex Character Classes
==============================

From:  Hans Aberg
Date:  Tue, 11 Jan 2005 20:20:25 +0100

I have hacked together some functions generating Flex style regular
expressions for the Unicode encodings UTF-8 and UTF-32 (big/endian). They
are written in Haskell, using Hugs <http://haskell.org/>. The input for each
one of these functions is a pair of Haskell Int's x y (same as a C 32-bit
int), designating a closed character interval [x-y] of Unicode numbers. The
function converts this to a regular expression matching this Unicode
character class as it appears in the function specific Unicode encoding.
None of these functions treat the excluded Unicode numbers U+D800 to U+DFFF
U+FFFE to U+FFFF different form other Unicode numbers. One can thus generate
regular expressions for these numbers to generate error messages. In
addition, I have supplied functions to generate regular expression for the
overloaded UTF-8 multibytes, illegal in UTF-8, also with the intent to
enable one to generate error message for such numbers. (More details below.)

One can use the functions to generate regular expressions to plug into Flex,
or one might integrate these functions into a future Unicode version of
Flex. Dwelling a bit on the latter question: It is possible to admit UTF-8
and UTF-32 character classes to exist side by side. The point of doing this
might be if one wants to write a lexer that can, say via start conditions,
switch between different encodings. One cannot, though, mix different
encodings in the same character class. Therefore, a Unicode extension of
Flex might look as follows:

The .l files are assumed to be in UTF-8. The standard character classes
[x-y] are extended to generate UTF-8 regular expressions. Writing \u........
translates into UTF-8 regular expressions. Writing \U........ translates
into bigendian UTF-32 regular expressions. Writing \L........ translates
into lowendian UTF-32 regular expressions. If big (resp. low) endian numbers
are used in a [x-y] character class, all numbers in that class must be big
(resp. low) endian, and the character class is translated into a big (resp.
low) endian UTF-32 regular expression.

Returning to the functions in the attached file Unicode.hs: all of type
  urToRegU8 :: Int -> Int -> Reg   -- Unicode to UTF-8 reg ex.
  urToRegU32 :: Int -> Int -> Reg  -- Unicode to bigendian UTF-32 reg ex.
  urToRegU32L :: Int -> Int -> Reg -- Unicode to lowendian UTF-32 reg ex.

  urToRegU8B1 :: Int -> Int -> Reg  -- Unicode to 1-byte UTF-8 reg ex.
  urToRegU8B2 :: Int -> Int -> Reg  -- Unicode to 2-byte UTF-8 reg ex.
  urToRegU8B3 :: Int -> Int -> Reg  -- Unicode to 3-byte UTF-8 reg ex.
  urToRegU8B4 :: Int -> Int -> Reg  -- Unicode to 4-byte UTF-8 reg ex.
  urToRegU8B5 :: Int -> Int -> Reg  -- Unicode to 5-byte UTF-8 reg ex.
  urToRegU8B6 :: Int -> Int -> Reg  -- Unicode to 6-byte UTF-8 reg ex.

Just compute, for example:
Unicode> urToRegU8 0 0xFFFF
[\0-\x7F]|[\xC2-\xDF][\x80-\xBF]|(\xE0[\xA0-\xBF]|[\xE1-\xEF][\x80-\xBF])
[\x80-\xBF]
Unicode> urToRegU32 0x00010000 0x001FFFFF
\0[\x01-\x1F][\0-\xFF][\0-\xFF]
Unicode> urToRegU32L 0x00010000 0x001FFFFF
[\x01-\x1F][\0-\xFF][\0-\xFF]\0

  Hans Aberg
