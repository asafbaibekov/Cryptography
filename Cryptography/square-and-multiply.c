//
//  square-and-multiply.c
//  Cryptography
//
//  Created by Asaf Baibekov on 11/11/2022.
//

#include "square-and-multiply.h"

void print_for_exponent(int x, int e, int p) {
	int64_t result = exponent(x, e, p);
	printf("%d^%d (mod %d) === %lld\n", x, e, p, result);
}

// x^e (mod p)
int64_t exponent(int64_t x, int64_t y, int64_t mod) {
	if (y == 0)
		return 1;
	int64_t e = exponent(x, y / 2, mod) % mod;
	e = (e * e) % mod;
	if (y % 2 == 1)
		e = (e * x) % mod;
	return e;
}
