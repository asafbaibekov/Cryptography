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
