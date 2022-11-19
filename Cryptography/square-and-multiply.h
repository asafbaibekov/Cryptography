//
//  square-and-multiply.h
//  Cryptography
//
//  Created by Asaf Baibekov on 11/11/2022.
//

#ifndef square_and_multiply_h
#define square_and_multiply_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// x^e (mod p)
void print_for_exponent(int x, int e, int p);

long long exponent(long long x, long long y, long long mod);

#endif /* square_and_multiply_h */
