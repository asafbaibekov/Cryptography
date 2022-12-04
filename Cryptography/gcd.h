//
//  gcd.h
//  Cryptography
//
//  Created by Asaf Baibekov on 29/10/2022.
//

#ifndef gcd_h
#define gcd_h

#include <stdio.h>

void scan_for_gcd(int *a, int *b);

void print_gcd(long long a, long long b);

int gcd(int a, int b);

void extended_gcd(long long a, long long b, long long *gcd, long long *m, long long *n);

#endif /* gcd_h */
