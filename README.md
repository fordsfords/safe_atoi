# safe_atoi
C Macro for converting Ascii to integer.

## License

I want there to be NO barriers to using this code, so I am releasing it to the public domain.  But "public domain" does not have an internationally agreed upon definition, so I use CC0:

Copyright 2020 Steven Ford http://geeky-boy.com and licensed
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

This C file is only intended to deliver a macro that I use a
fair amount: SAFE_ATOI.

See [strtol preferred over atoi https://blog.geeky-boy.com/2014/04/strtoul-preferred-over-atoi.html]
for why I wrote this macro (short version: strtol detects user mistakes).
But note that the macro has evolved since that blog post was written.

The C program "safe_atoi.c" tests the macro, but you should use it
by simply copy/pasting the macro into your own source files.

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

## Change the Error Handling

You probably want to change the error handling in these macros.
Currently, if there is an error,
it prints a programmer-friendly (i.e. not-very-user-friendly) message to
standard error and returns with "errno" set to non-zero.
But printing errors (especially non-user-friendly ones) is generally
considered poor form for general utilities,
so many users will want to delete the "printf"s and add better,
context-appropriate messages at the caller.

But in some use cases, like validating command-line options for tools,
user-friendliness is not as important, and it is convenient for the
macro to print a programmer-friendly error message and then exit.
In those cases, leave the "printf"s, and add an "exit(1)" after each.

Note that, unlike the strtol() family of functions,
the caller of this macro does *not* need to set errno to zero.
