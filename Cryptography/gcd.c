//
//  gcd.c
//  Cryptography
//
//  Created by Asaf Baibekov on 29/10/2022.
//

#include "gcd.h"

void scan_for_gcd(int *a, int *b) {
	printf("scan for gcd:\n");
	printf("enter a = ");
	scanf("%d", a);
	printf("enter b = ");
	scanf("%d", b);
}

void print_gcd(int64_t a, int64_t b) {
	int64_t gcd = 0;
	int64_t m = 0;
	int64_t n = 0;
	extended_gcd(a, b, &gcd, &m, &n);
	printf("%lld = %lld * %lld + %lld * %lld\n", gcd, m, a, n, b);
}

uint64_t gcd(uint64_t a, uint64_t b) {
	if (a == 0) return b;
	if (b == 0) return a;
	if (a < b)
		return gcd(b, a);
	if (a % b == 0)
		return b;
	return gcd(b, a % b);
}

void extended_gcd(int64_t a, int64_t b, int64_t *gcd, int64_t *m, int64_t *n) {
	if (a == 0) {
		*gcd = b;
		*m = 0;
		*n = 1;
		return;
	}
	int64_t m1, n1;
	extended_gcd(b % a, a, gcd, &m1, &n1);
	*m = n1 - (b / a) * m1;
	*n = m1;
}
