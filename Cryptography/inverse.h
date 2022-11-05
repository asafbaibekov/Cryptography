//
//  inverse.h
//  Cryptography
//
//  Created by Asaf Baibekov on 05/11/2022.
//

#ifndef inverse_h
#define inverse_h

#include <stdio.h>
#include "gcd.h"

void scan_for_inverse(int *a, int *n);

void print_inverse(int a, int n);

int inverse(int a, int n);

#endif /* inverse_h */
