//
//  dsa.c
//  Cryptography
//
//  Created by Asaf Baibekov on 07/01/2023.
//

#include "dsa.h"

uint64_t dsa_private_key_d;

void DSA_sign_and_verify(uint64_t p, uint64_t q, int alpha, int message) {
	printf("message: %d\n", message);
	uint64_t public_key = DSA_generate_keyPair(p, q, alpha);
	printf("public_key: %lld\n", public_key);
	uint64_t r, s;
	DSA_sign(p, q, alpha, message, &r, &s);
	printf("r: %lld, s: %lld\n", r, s);
	bool isVerified = DSA_verify(p, q, alpha, public_key, r, s, message);
	printf("isVerified: %s\n", isVerified ? "true" : "false");
}

uint64_t rand_uint64(void) {
	uint64_t result = 0;
	for (int i = 0; i < 64; i++) {
		result = result * 2 + rand() % 2;
	}
	return result;
}

uint64_t DSA_generate_keyPair(uint64_t p, uint64_t q, int alpha) {
	dsa_private_key_d = rand_uint64() % q;
	return exponent(alpha, dsa_private_key_d, p);
}

void DSA_sign(uint64_t p, uint64_t q, int alpha, int message, uint64_t *r, uint64_t *s) {
	do {
		int64_t *ephemeral_key_inv;
		do {
			uint64_t ephemeral_key;
			ephemeral_key = rand_uint64() % q;
			*r = exponent(alpha, ephemeral_key, p) % q;
			ephemeral_key_inv = inverse(ephemeral_key, q);
		}
		while (ephemeral_key_inv == NULL);
		*s = ((message + dsa_private_key_d * *r) * *ephemeral_key_inv) % q;
		free(ephemeral_key_inv);
	} while (*s == 0);
}

bool DSA_verify(uint64_t p, uint64_t q, int alpha, uint64_t public_key, uint64_t r, uint64_t s, int message) {
	int64_t *w = inverse(s, q);
	if (w == NULL) return false;
	uint64_t u1 = (*w * message) % q;
	uint64_t u2 = (*w * r) % q;
	free(w);
	uint64_t v = exponent(alpha, u1, p) * exponent(public_key, u2, p);
	v %= p;
	v %= q;
	return v == r;
}
