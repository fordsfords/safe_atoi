# safe_atoi
C Macro for converting Ascii to integer.

## License

I want there to be NO barriers to using this code, so I am releasing it to the public domain.  But "public domain" does not have an internationally agreed upon definition, so I use CC0:

Copyright 2021 Steven Ford http://geeky-boy.com and licensed
"public domain" style under
[CC0](http://creativecommons.org/publicdomain/zero/1.0/): 
![CC0](https://licensebuttons.net/p/zero/1.0/88x31.png "CC0")

To the extent possible under law, the contributors to this project have
waived all copyright and related or neighboring rights to this work.
In other words, you can use this code for any purpose without any
restrictions.  This work is published from: United States.  The project home
is https://github.com/fordsfords/pgen

To contact me, Steve Ford, project owner, you can find my email address
at http://geeky-boy.com.  Can't see it?  Keep looking.


## Introduction

This C include file is only intended to deliver a macro that I use a
fair amount: SAFE_ATOI.

See [strtol preferred over atoi](https://blog.geeky-boy.com/2014/04/strtoul-preferred-over-atoi.html)
for why I wrote this macro (short version: strtol detects user mistakes).
But note that the macro has evolved since that blog post was written.

The C program "safe_atoi.c" tests the macro, but you should use it
by simply copy/pasting the macro from safe_atoi.h into your own source files.

Here's an example usage:
````c
  int i;
  SAFE_ATOI(optarg, i);
  if (errno != 0) exit(1);
````
This assumes that "optarg" is a normal, null-terminated C string.

Note that this macro requires that the Ascii string contain only the
number to be converted.
No extraneous characters are allowed.
For example:
````c
  int i;
  SAFE_ATOI("123 ", i);
  if (errno != 0) exit(1);
````
will fail (whitespace not stripped).

When the macro returns, you must examine "errno" to determine if there
was an error.

## Automatic Data Type Checking

Normal APIs tend to have different versions for different integer data types
(char, short, int, long, long long).
The SAFE_ATOI macro does a reasonable job of detecting the data type of
the variable you pass, and doing error checking appropriate for that
type.

For example:
````c
  short s;
  SAFE_ATOI("32767", s);
  if (errno != 0) exit(1);
````
will succeed. Whereas:
````c
  char c;
  SAFE_ATOI("32767", c);
  if (errno != 0) exit(1);
````
will fail.

This will also fail:
````c
  unsigned int ui;
  SAFE_ATOI("-1", ui);
  if (errno != 0) exit(1);
````

However, the macro is not able to detect an illegal use of a negative
value for an unsigned 64-bit variable
I.e.
````c
  unsigned long long ull;
  SAFE_ATOI("-1", ull);
  if (errno != 0) exit(1);
````
will succeed.


## Portability

I tried to make this pretty portable.
It should work on Unix and Windows, 32 and 64 bit,
with at least with fairly normal processors.

But there are a few things that will break the code on some
esoteric platforms.

1. The test code generally assumes that a "char" is 8 bits, "short" is 16 bits,
"int" is 32-bits, "long" can be 32 or 64 bits, and "long long" is 64 bits.
The actual macro code only assumes "long long" is 64-bits.
2. The "fs_[9]" array is indexed by "sizeof(r_)".
It assumes that r_ will only ever be 1, 2, 4, or 8 bytes long.
3. Strangely, the LLVM C compiler on my Mac throws two warnings:
````
safe_atoi.c:378:32: warning: integer literal is too large to be represented in a
      signed integer type, interpreting as unsigned
      [-Wimplicitly-unsigned-literal]
    ASSRT(errno==0); ASSRT(l==-9223372036854775808l);
                               ^
safe_atoi.c:445:31: warning: integer literal is too large to be represented in a
      signed integer type, interpreting as unsigned
      [-Wimplicitly-unsigned-literal]
  ASSRT(errno==0); ASSRT(ll==-9223372036854775808ll);
                              ^
````
But those literals are perfectly legal "long long" values,
so what's the problem???
