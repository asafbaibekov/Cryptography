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

void print_gcd(long long a, long long b) {
	long long gcd = 0;
	long long m = 0;
	long long n = 0;
	extended_gcd(a, b, &gcd, &m, &n);
	printf("%lld = %lld * %lld + %lld * %lld\n", gcd, m, a, n, b);
}

int gcd(int a, int b) {
	if (a < b)
		return gcd(b, a);
	if (a % b == 0)
		return b;
	return gcd(b, a % b);
}

void extended_gcd(long long a, long long b, long long *gcd, long long *m, long long *n) {
	if (a == 0) {
		*gcd = b;
		*m = 0;
		*n = 1;
		return;
	}
	long long m1, n1;
	extended_gcd(b % a, a, gcd, &m1, &n1);
	*m = n1 - (b / a) * m1;
	*n = m1;
}
