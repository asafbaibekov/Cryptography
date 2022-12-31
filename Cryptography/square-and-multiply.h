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
#include <stdint.h>
#include <string.h>

// x^e (mod p)
void print_for_exponent(int x, int e, int p);

int64_t exponent(int64_t x, int64_t y, int64_t mod);

#endif /* square_and_multiply_h */
