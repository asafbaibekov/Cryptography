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

void print_gcd(int a, int b) {
	int gcd = 0;
	int m = 0;
	int n = 0;
	extended_gcd(a, b, &gcd, &m, &n);
	printf("%d = %d * %d + %d * %d\n", gcd, m, a, n, b);
}

int gcd(int a, int b) {
	if (a < b)
		return gcd(b, a);
	if (a % b == 0)
		return b;
	return gcd(b, a % b);
}

void extended_gcd(int a, int b, int *gcd, int *m, int *n) {
	if (a == 0) {
		*gcd = b;
		*m = 0;
		*n = 1;
		return;
	}
	
	int q = a / b;
	int r = a % b;
	
	extended_gcd(b, r, gcd, m, n);
	
	int t = *n;
	*n = *m - q * *n;
	*m = t;
}
