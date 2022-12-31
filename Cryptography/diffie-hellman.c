//
//  diffie-hellman.c
//  Cryptography
//
//  Created by Asaf Baibekov on 04/12/2022.
//

#include "diffie-hellman.h"
int dh_private_key_a;
int dh_private_key_b;

int64_t DH_generate_keyPair(int64_t p, int alpha) {
	srand((unsigned int) time(NULL));
	dh_private_key_a = rand();
	dh_private_key_b = rand();
	return exponent(alpha, dh_private_key_a, p);
}

void DH_encrypt(int64_t p, int alpha, int64_t Kpub, int message, int64_t *ephemeral_key, int64_t *cipher) {
	*ephemeral_key = exponent(alpha, dh_private_key_b, p);
	int64_t Km = exponent(Kpub, dh_private_key_b, p);
	*cipher = (message * Km) % p;
}

void DH_decrypt(int64_t p, int alpha, int64_t Keph, int64_t cipher, int64_t *message) {
	int64_t km = exponent(Keph, dh_private_key_a, p);
	int64_t *km_inverse = inverse(km, p);
	if (km_inverse == NULL) return;
	*message = (cipher * *km_inverse) % p;
	free(km_inverse);
}
