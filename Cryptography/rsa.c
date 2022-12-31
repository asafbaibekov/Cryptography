//
//  rsa.c
//  Cryptography
//
//  Created by Asaf Baibekov on 31/12/2022.
//

#include "rsa.h"

uint16_t rsa_private_key_p;
uint16_t rsa_private_key_q;

void RSA_generate_keyPair(uint32_t *e, uint32_t *n) {
	srand((unsigned int) time(NULL));
	rsa_private_key_p = generate_16bits_prime(NULL);
	rsa_private_key_q = generate_16bits_prime(NULL);
	*n = rsa_private_key_p * rsa_private_key_q;
	uint32_t phi_n = (rsa_private_key_p - 1) * (rsa_private_key_q - 1);
	do {
		*e = rand();
	}
	while (gcd(phi_n, *e) != 1 || *e >= phi_n);
}

void RSA_encrypt(uint64_t n, uint64_t Kpub, uint64_t message, uint64_t *cipher) {
	*cipher = exponent(message, Kpub, n);
}

void RSA_decrypt(int64_t Kpub, uint64_t cipher, int64_t *message) {
	uint32_t n = rsa_private_key_p * rsa_private_key_q;
	uint32_t phi_n = (rsa_private_key_p - 1) * (rsa_private_key_q - 1);
	int64_t *d = inverse(Kpub, phi_n);
	if (d == NULL) return;
	*message = exponent(cipher, *d, n);
}
