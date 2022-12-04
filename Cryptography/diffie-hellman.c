//
//  diffie-hellman.c
//  Cryptography
//
//  Created by Asaf Baibekov on 04/12/2022.
//

#include "diffie-hellman.h"
int private_key_a;
int private_key_b;

long long generate_keyPair(long long p, int alpha) {
	srand((unsigned int) time(NULL));
	private_key_a = rand();
	private_key_b = rand();
	return exponent(alpha, private_key_a, p);
}

void DH_encrypt(long long p, int alpha, long long Kpub, int message, long long *ephemeral_key, long long *cipher) {
	*ephemeral_key = exponent(alpha, private_key_b, p);
	long long Km = exponent(Kpub, private_key_b, p);
	*cipher = (message * Km) % p;
}

void DH_decrypt(long long p, int alpha, long long Keph, long long cipher, long long *message) {
	long long km = exponent(Keph, private_key_a, p);
	long long *km_inverse = inverse(km, p);
	if (km_inverse == NULL) return;
	*message = (cipher * *km_inverse) % p;
	free(km_inverse);
}
