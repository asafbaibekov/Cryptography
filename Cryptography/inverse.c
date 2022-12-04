//
//  inverse.c
//  Cryptography
//
//  Created by Asaf Baibekov on 05/11/2022.
//

#include "inverse.h"

void scan_for_inverse(int *a, int *n) {
	printf("scan for inverse:\n");
	printf("enter a = ");
	scanf("%d", a);
	printf("enter n = ");
	scanf("%d", n);
}

void print_inverse(int a, int n) {
	int g = gcd(a, n);
	printf("%dx === %d (mod %d)\n", a, g, n);
	long long *inv = inverse(a, n);
	if (inv == NULL) {
		printf("Can't find the inverse between %d and %d\n", a, n);
		printf("because the gcd between them is %d\n", g);
		printf("and it isn't equal to 1\n");
		return;
	}
	printf("x === %lld (mod %d)\n", *inv, n);
	free(inv);
}

long long *inverse(long long a, long long n) {
	long long gcd, x, y;
	extended_gcd(a, n, &gcd, &x, &y);
	if (gcd != 1) return NULL;
	a %= n;
	long long *toRet = malloc(sizeof(long long));
	*toRet = (x < 0) ? x + n : x;
	return toRet;
}
