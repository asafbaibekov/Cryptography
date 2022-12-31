//
//  primary-test.h
//  Cryptography
//
//  Created by Asaf Baibekov on 19/11/2022.
//

#ifndef primary_test_h
#define primary_test_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include "gcd.h"
#include "square-and-multiply.h"

bool is_carmichael_number(int n);

bool single_test(uint32_t d, uint32_t n);

bool check_primility(uint32_t n);

uint32_t rand_32_bits_number(void);

uint32_t generate_long_prime(int *attempts);

#endif /* primary_test_h */
