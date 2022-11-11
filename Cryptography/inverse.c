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
	int gcd, x, y;
	GCD(a, n, &gcd, &x, &y);
	printf("%dx === %d (mod %d)\n", a, gcd, n);
	int *inv = inverse(a, n);
	if (inv == NULL) {
		printf("Can't find the inverse between %d and %d\n", a, n);
		printf("because the gcd between them is %d\n", gcd);
		printf("and it isn't equal to 1\n");
		return;
	}
	printf("x === %d (mod %d)\n", *inv, n);
	free(inv);
}

int *inverse(int a, int n) {
	int gcd, x, y;
	GCD(a, n, &gcd, &x, &y);
	if (gcd != 1) return NULL;
	a %= n;
	int *toRet = malloc(sizeof(int));
	*toRet = (x < 0) ? x + n : x;
	return toRet;
}
