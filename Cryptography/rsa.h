//
//  rsa.h
//  Cryptography
//
//  Created by Asaf Baibekov on 31/12/2022.
//

#ifndef rsa_h
#define rsa_h

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "inverse.h"
#include "square-and-multiply.h"
#include "primary-test.h"

void RSA_generate_keyPair(uint32_t *e, uint32_t *n);

void RSA_encrypt(uint64_t n, uint64_t Kpub, uint64_t message, uint64_t *cipher);

void RSA_decrypt(int64_t Kpub, uint64_t cipher, int64_t *message);

#endif /* rsa_h */
