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
	if (gcd != 1) {
		printf("Can't find the inverse between %d and %d\n", a, n);
		printf("because the gcd between them %d isn't equal to 1\n", gcd);
		return;
	}
	printf("%dx === %d (mod %d)\n", a, gcd, n);
	int inv = inverse(a, n);
	printf("x === %d (mod %d)\n", inv, n);
}

int inverse(int a, int n) {
	int gcd, x, y;
	GCD(a, n, &gcd, &x, &y);
	a %= n;
	for (int i = 0; i < n; i++)
		if ((a * i) % n == gcd)
			return i;
	return 0;
}
