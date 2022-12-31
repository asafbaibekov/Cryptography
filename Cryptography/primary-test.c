//
//  primary-test.c
//  Cryptography
//
//  Created by Asaf Baibekov on 19/11/2022.
//

#include "primary-test.h"
#define ATTEMPTS 20

bool is_carmichael_number(int n) {
	for (int a = 2; a < n; a++) {
		int64_t g = gcd(a, n);
		uint64_t e = exponent(a, n - 1, n);
		if (g == 1 && e != 1) {
			return false;
		}
	}
	return true;
}

bool single_test(uint32_t m, uint32_t n) {
	int a = 2 + rand() % (n - 4);

	uint64_t x = exponent(a, m, n);
	if (x < 0)
		x = x + n;
	if (x == 1 || x == n - 1)
		return true;

	while (m != n-1) {
		x = (x * x) % n;
		m *= 2;
		if (x == 1)
			return false;
		if (x == n - 1)
			return true;
	}
	return false;
}

bool check_primility(uint32_t n) {
	if (n <= 1 || n == 4)
		return false;
	if (n <= 3)
		return true;
	
	uint32_t m = n - 1;
	while (m % 2 == 0)
		m /= 2;
	for (int i = 0; i < ATTEMPTS; i++)
		if (!single_test(m, n))
			return false;
	return true;
}

uint32_t rand_32_bits_number(void) {
	uint32_t toRet = 0;
	char array[32];
	array[0] = 1;
	for (char i = 1; i < 31; i++) {
		int r = rand();
		array[i] = r % 2;
	}
	array[31] = 1;
	for (char i = 0; i < 32; i++) {
		toRet += array[i] * pow(2, i);
	}
	return toRet;
}

uint32_t generate_32bits_prime(int *attempts) {
	if (attempts != NULL) *attempts = 0;
	int32_t number = rand_32_bits_number();
	while (check_primility(number) == false) {
		int32_t newnumber = rand_32_bits_number();
		while(number == newnumber) {
			newnumber = rand_32_bits_number();
		}
		number = newnumber;
		if (attempts != NULL) (*attempts)++;
	}
	return number;
}
