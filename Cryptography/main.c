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
	long long prime = generate_long_prime(&attempts);
	printf("generated long prime: %lld\n", prime);
	printf("number of attemtps are: %d\n", attempts);
}

void main_diffie_hellman(void) {
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
}

void main_elliptic_curve(void) {
	EllipticCurve *curve = initEllipticCurve(1, 6, 11);
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
	return 0;
}
