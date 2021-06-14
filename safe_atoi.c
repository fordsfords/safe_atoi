/* safe_atol.c */
/*
# This code and its documentation is Copyright 2020 Steven Ford, http://geeky-boy.com
# and licensed "public domain" style under Creative Commons "CC0":
#   http://creativecommons.org/publicdomain/zero/1.0/
# To the extent possible under law, the contributors to this project have
# waived all copyright and related or neighboring rights to this work.
# In other words, you can use this code for any purpose without any
# restrictions.  This work is published from: United States.  The project home
# is https://github.com/fordsfords/safe_atol
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>


#define SAFE_ATOI(a_,l_) do { \
  unsigned long long fs_[9] = { \
    0, 0xff, 0xffff, 0, 0xffffffff, 0, 0, 0, 0xffffffffffffffff }; \
  errno = 0; \
  (l_) = fs_[sizeof(l_)]; \
  if ((l_) < 0) { /* Is result a signed value? */ \
    char *in_a_ = a_;  char *temp_ = NULL;  long long llresult_; \
    if (strlen(in_a_) > 2 && *in_a_ == '0' && *(in_a_ + 1) == 'x') { \
      llresult_ = strtoll(in_a_ + 2, &temp_, 16); \
    } else { \
      llresult_ = strtoll(in_a_, &temp_, 10); \
    } \
    if (errno != 0 || temp_ == in_a_ || temp_ == NULL || *temp_ != '\0') { \
      if (errno == 0) { \
        errno = EINVAL; \
      } \
      fprintf(stderr, "%s:%d, Error, invalid number for %s: '%s'\n", \
         __FILE__, __LINE__, #l_, in_a_); \
    } else { /* strtol thinks success; check for overflow. */ \
      (l_) = llresult_; /* "return" value of macro */ \
      if ((l_) != llresult_) { \
        fprintf(stderr, "%s:%d, %s over/under flow: '%s'\n", \
           __FILE__, __LINE__, #l_, in_a_); \
        errno = ERANGE; \
      } \
    } \
  } else { \
    char *in_a_ = a_;  char *temp_ = NULL;  unsigned long long llresult_; \
    if (strlen(in_a_) > 2 && *in_a_ == '0' && *(in_a_ + 1) == 'x') { \
      llresult_ = strtoull(in_a_ + 2, &temp_, 16); \
    } else { \
      llresult_ = strtoull(in_a_, &temp_, 10); \
    } \
    if (errno != 0 || temp_ == in_a_ || temp_ == NULL || *temp_ != '\0') { \
      if (errno == 0) { \
        errno = EINVAL; \
      } \
      fprintf(stderr, "%s:%d, Error, invalid number for %s: '%s'\n", \
         __FILE__, __LINE__, #l_, in_a_); \
    } else { /* strtol thinks success; check for overflow. */ \
      (l_) = llresult_; /* "return" value of macro */ \
      if ((l_) != llresult_) { \
        fprintf(stderr, "%s:%d, %s over/under flow: '%s'\n", \
           __FILE__, __LINE__, #l_, in_a_); \
        errno = ERANGE; \
      } \
    } \
  } \
} while (0)


#define ASSRT(cond_) do { \
  if (! (cond_)) { \
    fprintf(stderr, "%s:%d, ERROR: '%s' not true\n", \
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

  return 0;
}  /* main */
