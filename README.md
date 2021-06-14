# safe_atoi
C Macros for converting ascii to integer.

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

This C file is only intended to deliver a simple pair of macro that I use a
fair amount: SAFE_ATOI and SAFE_ATOU.

See [strtol preferred over atoi https://blog.geeky-boy.com/2014/04/strtoul-preferred-over-atoi.html]
for why these macros exists.
But note that the macros have evolved somewhat since that blog post
was written.

The C program "safe_atoi.c" tests the macros, but you should use it
by cutting-and-pasting the macros into your own source files.

## Change the Error Handling

You probably want to change the error handling in these macros.
Currently, if there is an error,
it prints a message to standard error and returns with "errno" non-zero.
But printing errors is generally considered poor form for utility macros
so many users will want to delete the "printf"s.

But in some use cases, like validating command-line options,
it is convenient for the macro to print an error
message and then exit.
In those cases, leave the "printf"s in place,
and add an "exit(1)" after each.
