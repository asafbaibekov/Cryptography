//
//  diffie-hellman.h
//  Cryptography
//
//  Created by Asaf Baibekov on 04/12/2022.
//

#ifndef diffie_hellman_h
#define diffie_hellman_h

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "inverse.h"
#include "square-and-multiply.h"

#define BIG_PRIME 2291447117

int64_t DH_generate_keyPair(int64_t p, int alpha);

void DH_encrypt(int64_t p, int alpha, int64_t Kpub, int message, int64_t *ephemeral_key, int64_t *cipher);

void DH_decrypt(int64_t p, int alpha, int64_t Keph, int64_t cipher, int64_t *message);

#endif /* diffie_hellman_h */
