//
//  diffie-hellman.h
//  Cryptography
//
//  Created by Asaf Baibekov on 04/12/2022.
//

#ifndef diffie_hellman_h
#define diffie_hellman_h

#include <stdio.h>
#include <time.h>
#include "inverse.h"
#include "square-and-multiply.h"

#define BIG_PRIME 2291447117

long long DH_generate_keyPair(long long p, int alpha);

void DH_encrypt(long long p, int alpha, long long Kpub, int message, long long *ephemeral_key, long long *cipher);

void DH_decrypt(long long p, int alpha, long long Keph, long long cipher, long long *message);

#endif /* diffie_hellman_h */
