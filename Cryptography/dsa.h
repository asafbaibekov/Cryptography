//
//  dsa.h
//  Cryptography
//
//  Created by Asaf Baibekov on 07/01/2023.
//

#ifndef dsa_h
#define dsa_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "gcd.h"
#include "inverse.h"
#include "square-and-multiply.h"

void DSA_sign_and_verify(uint64_t p, uint64_t q, int alpha, int message);

uint64_t DSA_generate_keyPair(uint64_t p, uint64_t q, int alpha);

void DSA_sign(uint64_t p, uint64_t q, int alpha, int message, uint64_t *r, uint64_t *s);

bool DSA_verify(uint64_t p, uint64_t q, int alpha, uint64_t public_key, uint64_t r, uint64_t s, int message);

#endif /* dsa_h */
