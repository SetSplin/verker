#ifndef __MEMCHR_H__
#define __MEMCHR_H__

#include "kernel_definitions.h"

/*@ requires \typeof(s) <: \type(u8 *);
    requires \valid((u8 *)s+(0..n-1));
    assigns \nothing;
    behavior found:
       assumes \exists u8 *p; (u8 *)s <= p < (u8 *)s + n && *p == (u8 %) c;
       ensures s <= \result <= s + n;
       ensures \forall u8 *p; (u8 *)s <= p < (u8 *)\result ==> *p != (u8 %) c;
       ensures *((u8 *)\result) == (u8 %)c;
    behavior not_exists:
       assumes \forall u8 *p; (u8 *)s <= p < (u8 *)s + n ==> *p != (u8 %) c;
       ensures \result == \null;
    complete behaviors;
    disjoint behaviors;
 */
void *memchr(const void *s, int c, size_t n);

#endif // __MEMCHR_H__
