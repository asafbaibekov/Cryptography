//
//  square-and-multiply.c
//  Cryptography
//
//  Created by Asaf Baibekov on 11/11/2022.
//

#include "square-and-multiply.h"

void print_for_exponent(int x, int e, int p) {
	long long result = exponent(x, e, p);
	printf("%d^%d (mod %d) === %lld\n", x, e, p, result);
}

// x^e (mod p)
long long exponent(long long x, long long y, long long mod) {
	if (y == 0)
		return 1;
	long long e = exponent(x, y / 2, mod) % mod;
	e = (e * e) % mod;
	if (y % 2 == 1)
		e = (e * x) % mod;
	return e;
}
