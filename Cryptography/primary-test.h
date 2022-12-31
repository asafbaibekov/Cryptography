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

bool single_test(uint64_t d, uint64_t n);

bool check_primility(uint64_t n);

uint64_t rand_32_bits_number(void);

uint64_t generate_long_prime(int *attempts);

#endif /* primary_test_h */
