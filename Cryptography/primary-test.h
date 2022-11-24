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
#include "gcd.h"
#include "square-and-multiply.h"

bool is_carmichael_number(int n);

bool single_test(unsigned long long d, unsigned long long n);

bool check_primility(unsigned long long n);

int32_t rand_32_bits_number(void);

unsigned long long generate_long_prime(void);

#endif /* primary_test_h */
