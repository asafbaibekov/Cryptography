//
//  rc4.h
//  Cryptography
//
//  Created by Asaf Baibekov on 13/01/2023.
//

#ifndef rc4_h
#define rc4_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_key_stream(uint8_t *keystream);

uint8_t *RC4_init(char *key);

uint8_t *RC4_encrypt(char *string, uint8_t *keyStream);

char *RC4_decrypt(char *cipher, uint8_t *keyStream);

#endif /* rc4_h */
