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
#include "elliptic-curve.h"
#include "solve-dlp.h"
#include "rsa.h"

void main_gcd(void) {
	int a, b;
	scan_for_gcd(&a, &b);
	print_gcd(a, b);
}

void main_inverse(void) {
	int a, b;
	scan_for_inverse(&a, &b);
	print_inverse(a, b);
}

void main_crt(void) {
	print_demo_crt();
}

void main_square_and_multiply(void) {
	print_for_exponent(2, 79, 101);
	print_for_exponent(3, 197, 101);
}

void main_primary_test(void) {
	for (int i = 0; i < 100; i++) {
		int check = check_primility(i);
		if (check == 1)
			printf("is %d a prime number: %d\n", i, check);
	}
	printf("generating long prime...\n");
	int attempts = 0;
	srand((unsigned int) time(NULL));
	uint32_t prime = generate_32bits_prime(&attempts);
	printf("generated long prime: %u\n", prime);
	printf("number of attemtps are: %d\n", attempts);
}

void main_diffie_hellman(void) {
	int alpha = 2;
	int64_t public_key = DH_generate_keyPair(BIG_PRIME, alpha);
	uint64_t ephemeral_key;
	int64_t cipher_text;
	DH_encrypt(BIG_PRIME, alpha, public_key, 12345, &ephemeral_key, &cipher_text);
	
	printf("ephemeral_key: %lld\n", ephemeral_key);
	printf("cipher_text: %lld\n", cipher_text);
	
	int64_t message;
	DH_decrypt(BIG_PRIME, alpha, ephemeral_key, cipher_text, &message);
	printf("message: %lld\n", message);
}

void main_elliptic_curve(void) {
	EllipticCurve *curve = initEllipticCurve(1, 6, 11);
	printEllipticCurve(curve);
	printf("\n");
	EllipticCurvePoint *point1 = initEllipticCurvePoint(5, 9);
	EllipticCurvePoint *point2 = NULL;
	for (int i = 0; i < 13; i++) {
		EllipticCurvePoint *point_added = add_two_point_on_curve(point1, point2, curve);
		printf("%d:\t", i);
		printEllipticCurvePoint(point1);
		printf(" + ");
		printEllipticCurvePoint(point2);
		printf(" = \t");
		printEllipticCurvePoint(point_added);
		printf("\n");
		free(point2);
		point2 = copyEllipticCurvePoint(point_added);
		free(point_added);
	}
	free(point2);
	free(point1);
	free(curve);
}

void main_solve_dlp(void) {
	uint64_t *bsgs_private_key = BSGS_solve(2, 37, 131);
	if (bsgs_private_key != NULL) {
		printf("2^x === 37 mod 131\n");
		printf("x = %llu\n", *bsgs_private_key);
		free(bsgs_private_key);
	}
	
	printf("\n");
	
	int64_t *pollard_private_key = pollard_solve(3, 21, 59);
	if (pollard_private_key != NULL) {
		printf("3^x === 21 mod 59\n");
		printf("x = %lld\n", *pollard_private_key);
		free(pollard_private_key);
	}
}

void main_rsa(void) {
	uint32_t e, n;
	RSA_generate_keyPair(&e, &n);
	
	uint64_t cipher = 0;
	RSA_encrypt(n, e, 20, &cipher);
	printf("cipher: %lld\n", cipher);
	
	int64_t message = 0;
	RSA_decrypt(e, cipher, &message);
	printf("message: %lld\n", message);
}

int main(int argc, const char * argv[]) {
	printf("======================================\n");
	main_gcd();
	printf("======================================\n");
	main_inverse();
	printf("======================================\n");
	main_crt();
	printf("======================================\n");
	main_square_and_multiply();
	printf("======================================\n");
	main_primary_test();
	printf("======================================\n");
	main_diffie_hellman();
	printf("======================================\n");
	main_elliptic_curve();
	printf("======================================\n");
	main_solve_dlp();
	printf("======================================\n");
	main_rsa();
	return 0;
}
