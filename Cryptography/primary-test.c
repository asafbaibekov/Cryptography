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
		int g = gcd(a, n);
		long long e = exponent(a, n - 1, n);
		if (g == 1 && e != 1) {
			return false;
		}
	}
	return true;
}

bool single_test(unsigned long long m, unsigned long long n) {
	int a = 2 + rand() % (n - 4);

	long long x = exponent(a, m, n);
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

bool check_primility(unsigned long long n) {
	if (n <= 1 || n == 4)
		return false;
	if (n <= 3)
		return true;
	
	unsigned long long m = n - 1;
	while (m % 2 == 0)
		m /= 2;
	srand((unsigned int) time(NULL));
	for (int i = 0; i < ATTEMPTS; i++)
		if (!single_test(m, n))
			return false;
	return true;
}

unsigned long long rand_32_bits_number(void) {
	unsigned long long toRet = 0;
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

unsigned long long generate_long_prime(int *attempts) {
	if (attempts != NULL) *attempts = 0;
	long long number = rand_32_bits_number();
	while (check_primility(number) == false) {
		long long newnumber = rand_32_bits_number();
		while(number == newnumber) {
			newnumber = rand_32_bits_number();
		}
		number = newnumber;
		if (attempts != NULL) (*attempts)++;
	}
	return number;
}
