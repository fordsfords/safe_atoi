/* safe_atoi.c */
/*
# This code and its documentation is Copyright 2020 Steven Ford, http://geeky-boy.com
# and licensed "public domain" style under Creative Commons "CC0":
#   http://creativecommons.org/publicdomain/zero/1.0/
# To the extent possible under law, the contributors to this project have
# waived all copyright and related or neighboring rights to this work.
# In other words, you can use this code for any purpose without any
# restrictions.  This work is published from: United States.  The project home
# is https://github.com/fordsfords/safe_atoi
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>

#include "safe_atoi.h"


#define ASSRT(cond_) do { \
  if (! (cond_)) { \
    fprintf(stderr, "\n%s:%d, ERROR: '%s' not true\n", \
      __FILE__, __LINE__, #cond_); \
    abort(); \
  } \
} while (0)


int main(int argc, char **argv)
{
  char c;
  unsigned char uc;
  short s;
  unsigned short us;
  int i;
  unsigned int ui;
  long l;
  unsigned long ul;
  long long ll;
  unsigned long long ull;


  /* Char */
  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("", c);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("xyz", c);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("1-", c);
  ASSRT(errno!=0);


  SAFE_ATOI("0x7f", c);
  ASSRT(errno==0); ASSRT(c==127);

  SAFE_ATOI("00", c);
  ASSRT(errno==0); ASSRT(c==0);

  SAFE_ATOI("0127", c);
  ASSRT(errno==0); ASSRT(c==127);

  SAFE_ATOI("-1", c);
  ASSRT(errno==0); ASSRT(c==-1);

  SAFE_ATOI("-128", c);
  ASSRT(errno==0); ASSRT(c==-128);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("0128", c);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("-129", c);
  ASSRT(errno!=0);


  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("", uc);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("xyz", uc);
  ASSRT(errno!=0);

  SAFE_ATOI("0xff", uc);
  ASSRT(errno==0); ASSRT(uc==255);

  SAFE_ATOI("00", uc);
  ASSRT(errno==0); ASSRT(uc==0);

  SAFE_ATOI("0255", uc);
  ASSRT(errno==0); ASSRT(uc==255);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("-1", uc);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("0256", uc);
  ASSRT(errno!=0);


  /* Short */
  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("", s);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("xyz", s);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("1-", s);
  ASSRT(errno!=0);


  SAFE_ATOI("0x7fff", s);
  ASSRT(errno==0); ASSRT(s==32767);

  SAFE_ATOI("00", s);
  ASSRT(errno==0); ASSRT(s==0);

  SAFE_ATOI("032767", s);
  ASSRT(errno==0); ASSRT(s==32767);

  SAFE_ATOI("-1", s);
  ASSRT(errno==0); ASSRT(s==-1);

  SAFE_ATOI("-32768", s);
  ASSRT(errno==0); ASSRT(s==-32768);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("032768", s);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("-32769", s);
  ASSRT(errno!=0);


  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("", us);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("xyz", us);
  ASSRT(errno!=0);

  SAFE_ATOI("0xffff", us);
  ASSRT(errno==0); ASSRT(us==65535);

  SAFE_ATOI("00", us);
  ASSRT(errno==0); ASSRT(us==0);

  SAFE_ATOI("065535", us);
  ASSRT(errno==0); ASSRT(us==65535);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("-1", us);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("065536", us);
  ASSRT(errno!=0);


  /* Int */
  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("", i);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("xyz", i);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("1-", i);
  ASSRT(errno!=0);


  SAFE_ATOI("0x7fffffff", i);
  ASSRT(errno==0); ASSRT(i==2147483647);

  SAFE_ATOI("00", i);
  ASSRT(errno==0); ASSRT(i==0);

  SAFE_ATOI("02147483647", i);
  ASSRT(errno==0); ASSRT(i==2147483647ll);

  SAFE_ATOI("-1", i);
  ASSRT(errno==0); ASSRT(i==-1);

  SAFE_ATOI("-2147483648", i);
  ASSRT(errno==0); ASSRT(i==-2147483648ll);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("02147483648", i);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("-2147483649", i);
  ASSRT(errno!=0);


  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("", ui);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("xyz", ui);
  ASSRT(errno!=0);

  SAFE_ATOI("0xffffffff", ui);
  ASSRT(errno==0); ASSRT(ui==4294967295ll);

  SAFE_ATOI("00", ui);
  ASSRT(errno==0); ASSRT(ui==0);

  SAFE_ATOI("04294967295", ui);
  ASSRT(errno==0); ASSRT(ui==4294967295ll);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("-1", ui);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("04294967296", ui);
  ASSRT(errno!=0);


  /* Long */
  if (sizeof(long) == 4) {
    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("", l);
    ASSRT(errno!=0);

    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("xyz", l);
    ASSRT(errno!=0);

    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("1-", l);
    ASSRT(errno!=0);


    SAFE_ATOI("0x7fffffff", l);
    ASSRT(errno==0); ASSRT(l==2147483647ll);

    SAFE_ATOI("00", l);
    ASSRT(errno==0); ASSRT(l==0);

    SAFE_ATOI("02147483647", l);
    ASSRT(errno==0); ASSRT(l==2147483647ll);

    SAFE_ATOI("-1", l);
    ASSRT(errno==0); ASSRT(l==-1);

    SAFE_ATOI("-2147483648", l);
    ASSRT(errno==0); ASSRT(l==-2147483648ll);

    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("02147483648", l);
    ASSRT(errno!=0);

    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("-2147483649", l);
    ASSRT(errno!=0);


    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("", ul);
    ASSRT(errno!=0);

    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("xyz", ul);
    ASSRT(errno!=0);

    SAFE_ATOI("0xffffffffffffffff", ul);
    ASSRT(errno==0); ASSRT(ul==4294967295ll);

    SAFE_ATOI("00", ul);
    ASSRT(errno==0); ASSRT(ul==0);

    SAFE_ATOI("04294967295", ul);
    ASSRT(errno==0); ASSRT(ul==4294967295ll);

    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("-1", ul);
    ASSRT(errno!=0);

    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("04294967296", ul);
    ASSRT(errno!=0);
  } else {
    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("", l);
    ASSRT(errno!=0);

    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("xyz", l);
    ASSRT(errno!=0);

    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("1-", l);
    ASSRT(errno!=0);


    SAFE_ATOI("0x7fffffffffffffff", l);
    ASSRT(errno==0); ASSRT(l==9223372036854775807ll);

    SAFE_ATOI("00", l);
    ASSRT(errno==0); ASSRT(l==0);

    SAFE_ATOI("09223372036854775807", l);
    ASSRT(errno==0); ASSRT(l==9223372036854775807ll);

    SAFE_ATOI("-1", l);
    ASSRT(errno==0); ASSRT(l==-1);

    SAFE_ATOI("-9223372036854775808", l);
    ASSRT(errno==0); ASSRT(l==-9223372036854775808ll);

    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("09223372036854775808", l);
    ASSRT(errno!=0);

    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("-9223372036854775809", l);
    ASSRT(errno!=0);


    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("", ul);
    ASSRT(errno!=0);

    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("xyz", ul);
    ASSRT(errno!=0);

    SAFE_ATOI("0xffffffffffffffff", ul);
    ASSRT(errno==0); ASSRT(ul==18446744073709551615ull);

    SAFE_ATOI("00", ul);
    ASSRT(errno==0); ASSRT(ul==0);

    SAFE_ATOI("018446744073709551615", ul);
    ASSRT(errno==0); ASSRT(ul==18446744073709551615ull);

    /* The macro can't detect the illegal use of a negative value because
     * we are already at 64-bits, so the sign extension can't be counted on.
     * fprintf(stderr, "Expected error: ");
     * SAFE_ATOI("-1", ul);
     * ASSRT(errno!=0);
     */

    fprintf(stderr, "Expected error: ");
    SAFE_ATOI("018446744073709551616", ul);
    ASSRT(errno!=0);
  }

  /* Long long */
  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("", ll);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("xyz", ll);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("1-", ll);
  ASSRT(errno!=0);


  SAFE_ATOI("0x7fffffffffffffff", ll);
  ASSRT(errno==0); ASSRT(ll==9223372036854775807ll);

  SAFE_ATOI("00", ll);
  ASSRT(errno==0); ASSRT(ll==0);

  SAFE_ATOI("09223372036854775807", ll);
  ASSRT(errno==0); ASSRT(ll==9223372036854775807ll);

  SAFE_ATOI("-1", ll);
  ASSRT(errno==0); ASSRT(ll==-1);

  SAFE_ATOI("-9223372036854775808", ll);
  ASSRT(errno==0); ASSRT(ll==-9223372036854775808ll);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("09223372036854775808", ll);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("-9223372036854775809", ll);
  ASSRT(errno!=0);


  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("", ull);
  ASSRT(errno!=0);

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("xyz", ull);
  ASSRT(errno!=0);

  SAFE_ATOI("0xffffffffffffffff", ull);
  ASSRT(errno==0); ASSRT(ull==18446744073709551615ull);

  SAFE_ATOI("00", ull);
  ASSRT(errno==0); ASSRT(ull==0);

  SAFE_ATOI("018446744073709551615", ull);
  ASSRT(errno==0); ASSRT(ull==18446744073709551615ull);

  /* The macro can't detect the illegal use of a negative value because
   * we are already at 64-bits, so the sign extension can't be counted on.
   * fprintf(stderr, "Expected error: ");
   * SAFE_ATOI("-1", ul);
   * ASSRT(errno!=0);
   */

  fprintf(stderr, "Expected error: ");
  SAFE_ATOI("018446744073709551616", ul);
  ASSRT(errno!=0);

  printf("Success\n");
  return 0;
}  /* main */
