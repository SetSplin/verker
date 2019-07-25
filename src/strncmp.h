#ifndef __STRNCMP_H__
#define __STRNCMP_H__

#include "kernel_definitions.h"
#include "strlen.h"
#include "strnlen.h"

/**
 * strncmp - Compare two length-limited strings
 * @cs: One string
 * @ct: Another string
 * @count: The maximum number of bytes to compare
 */

/*@ axiomatic StrnCmp {
    logic bool strncmp(char *s1, char *s2, size_t n) =
       n <= 0 ?
          (bool)true
       :
          (s1[0] == s2[0] ?
	     (s1[0] == '\0' ? (bool)true : strncmp(s1 + 1, s2 + 1, (size_t)(n - 1)))
          :
	     (bool)false);

    lemma strncmp_shift:
       \forall char *s1, char *s2, size_t n;
          valid_str(s1) &&
          valid_str(s2) &&
          n > 0 ==>
          strncmp(s1, s2, n) ==>
          strncmp(s1 + 1, s2 + 1, (size_t)(n - 1));

    lemma strncmp_definition:
       \forall char *s1, char *s2, size_t n;
          valid_str(s1) &&
          valid_str(s2) ==>
          (\forall size_t i; 0 <= i < n ==> s1[i] == s2[i]) ==>
          strncmp(s1, s2, n);
    }
 */

int strncmp(const char *cs, const char *ct, size_t count);

#endif // __STRNCMP_H__
