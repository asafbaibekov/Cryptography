//
//  main.c
//  Cryptography
//
//  Created by Asaf Baibekov on 29/10/2022.
//

#include <stdio.h>
#include "gcd.h"

void print_gcd(int a, int b) {
	int gcd = 0;
	int m = 0;
	int n = 0;
	
	GCD(a, b, &gcd, &m, &n);
	
	printf("%d = %d * %d + %d * %d\n", gcd, m, a, n, b);
}

int main(int argc, const char * argv[]) {
	
	print_gcd(2464, 7469);
	printf("\n");
	print_gcd(4001, 2689);
	printf("\n");
	
	int a;
	int b;
	printf("enter a = ");
	scanf("%d", &a);
	printf("enter b = ");
	scanf("%d", &b);
	
	print_gcd(a, b);
	
	return 0;
}
