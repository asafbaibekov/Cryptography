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

void print_gcd(int a, int b);

void extended_gcd(int a, int b, int *gcd, int *m, int *n);

#endif /* gcd_h */
