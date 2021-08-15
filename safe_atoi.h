/* safe_atol.h */
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
#ifndef SAFE_ATOI_H
#define SAFE_ATOI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <errno.h>


#define SAFE_ATOI(a_,r_) do { \
  char *in_a_ = (a_); \
  int new_errno_; \
  unsigned long long fs_[9] = {  /* All '1's by variable size. */ \
    0, 0xff, 0xffff, 0, 0xffffffff, 0, 0, 0, 0xffffffffffffffff }; \
  (r_) = fs_[sizeof(r_)]; \
  if ((r_) < 0) { /* Is result a signed value? */ \
    char *temp_ = NULL;  long long llresult_; \
    if (strlen(in_a_) > 2 && in_a_[0] == '0' && (in_a_[1] == 'x' || in_a_[1] == 'X')) { \
      in_a_ += 2;  /* Skip past '0x'. */ \
      errno = 0; \
      llresult_ = strtoll(in_a_, &temp_, 16); \
      new_errno_ = errno; \
fprintf(stderr, "???1, new_errno_=%d, in_a_='%p', llresult_=%lld, temp_=%p\n", new_errno_, in_a_, llresult_, temp_); \
    } else { \
      errno = 0; \
      llresult_ = strtoll(in_a_, &temp_, 10); \
      new_errno_ = errno; \
    } \
    if (new_errno_ != 0 || temp_ == in_a_ || temp_ == NULL || *temp_ != '\0') { \
      if (new_errno_ == 0) { \
        new_errno_ = EINVAL; \
      } \
      fprintf(stderr, "%s:%d, Error, invalid number for %s: '%s'\n", \
         __FILE__, __LINE__, #r_, in_a_); \
    } else { /* strtol thinks success; check for overflow. */ \
      (r_) = llresult_; /* "return" value of macro */ \
      if ((r_) != llresult_) { \
        fprintf(stderr, "%s:%d, %s over/under flow: '%s'\n", \
           __FILE__, __LINE__, #r_, in_a_); \
        new_errno_ = ERANGE; \
      } \
    } \
  } else { \
    char *temp_ = NULL;  unsigned long long llresult_; \
    if (strlen(in_a_) > 2 && in_a_[0] == '0' && (in_a_[1] == 'x' || in_a_[1] == 'X')) { \
      in_a_ += 2;  /* Skip past '0x'. */ \
      errno = 0; \
      llresult_ = strtoull(in_a_, &temp_, 16); \
      new_errno_ = errno; \
    } else { \
      errno = 0; \
      llresult_ = strtoull(in_a_, &temp_, 10); \
      new_errno_ = errno; \
    } \
    if (new_errno_ != 0 || temp_ == in_a_ || temp_ == NULL || *temp_ != '\0') { \
      if (new_errno_ == 0) { \
        new_errno_ = EINVAL; \
      } \
      fprintf(stderr, "%s:%d, Error, invalid number for %s: '%s'\n", \
         __FILE__, __LINE__, #r_, in_a_); \
    } else { /* strtol thinks success; check for overflow. */ \
      (r_) = llresult_; /* "return" value of macro */ \
      if ((r_) != llresult_) { \
        fprintf(stderr, "%s:%d, %s over/under flow: '%s'\n", \
           __FILE__, __LINE__, #r_, in_a_); \
        new_errno_ = ERANGE; \
      } \
    } \
  } \
  errno = new_errno_; \
} while (0)


#ifdef __cplusplus
}
#endif

#endif  /* SAFE_ATOI_H */ 
