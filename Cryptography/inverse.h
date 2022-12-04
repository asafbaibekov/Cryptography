//
//  inverse.h
//  Cryptography
//
//  Created by Asaf Baibekov on 05/11/2022.
//

#ifndef inverse_h
#define inverse_h

#include <stdio.h>
#include <stdlib.h>
#include "gcd.h"

void scan_for_inverse(int *a, int *n);

void print_inverse(int a, int n);

void print_inverse_error(int a, int n, int gcd);

long long *inverse(long long a, long long n);

#endif /* inverse_h */
