//
//  gcd.h
//  Cryptography
//
//  Created by Asaf Baibekov on 29/10/2022.
//

#ifndef gcd_h
#define gcd_h

#include <stdio.h>
#include <stdint.h>

void scan_for_gcd(int *a, int *b);

void print_gcd(int64_t a, int64_t b);

int64_t gcd(int64_t a, int64_t b);

void extended_gcd(int64_t a, int64_t b, int64_t *gcd, int64_t *m, int64_t *n);

#endif /* gcd_h */
