//
//  main.c
//  Cryptography
//
//  Created by Asaf Baibekov on 29/10/2022.
//

#include <stdio.h>
#include "gcd.h"
#include "inverse.h"
#include "crt.h"
#include "square-and-multiply.h"
#include "primary-test.h"
#include "diffie-hellman.h"

int main(int argc, const char * argv[]) {
	printf("======================================\n");
	int a, b;
	scan_for_gcd(&a, &b);
	print_gcd(a, b);
	printf("======================================\n");
	scan_for_inverse(&a, &b);
	print_inverse(a, b);
	printf("======================================\n");
	print_demo_crt();
	printf("======================================\n");
	print_for_exponent(2, 79, 101);
	print_for_exponent(3, 197, 101);
	printf("======================================\n");
	
	for (int i = 0; i < 100; i++) {
		int check = check_primility(i);
		if (check == 1)
			printf("is %d a prime number: %d\n", i, check);
	}
	printf("generating long prime...\n");
	int attempts = 0;
	long long prime = generate_long_prime(&attempts);
	printf("generated long prime: %lld\n", prime);
	printf("number of attemtps are: %d\n", attempts);
	printf("======================================\n");
	
	int alpha = 2;
	long long public_key = generate_keyPair(BIG_PRIME, alpha);
	long long ephemeral_key;
	long long cipher_text;
	DH_encrypt(BIG_PRIME, alpha, public_key, 12345, &ephemeral_key, &cipher_text);
	
	printf("ephemeral_key: %lld\n", ephemeral_key);
	printf("cipher_text: %lld\n", cipher_text);
	
	long long message;
	DH_decrypt(BIG_PRIME, alpha, ephemeral_key, cipher_text, &message);
	printf("message: %lld\n", message);
	
	return 0;
}
