//
//  square-and-multiply.c
//  Cryptography
//
//  Created by Asaf Baibekov on 11/11/2022.
//

#include "square-and-multiply.h"

void print_for_exponent(int x, int e, int p) {
	uint64_t result = exponent(x, e, p);
	printf("%d^%d (mod %d) === %lld\n", x, e, p, result);
}

// x^e (mod p)
uint64_t exponent(uint64_t x, uint64_t y, uint64_t mod) {
	if (y == 0)
		return 1;
	uint64_t e = exponent(x, y / 2, mod) % mod;
	e = (e * e) % mod;
	if (y % 2 == 1)
		e = (e * x) % mod;
	return e;
}
