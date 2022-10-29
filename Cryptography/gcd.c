//
//  gcd.c
//  Cryptography
//
//  Created by Asaf Baibekov on 29/10/2022.
//

#include "gcd.h"

void GCD(int a, int b, int *gcd, int *m, int *n) {
	if (a == 0) {
		*gcd = b;
		*m = 0;
		*n = 1;
		return;
	}
	
	int q = a / b;
	int r = a % b;
	
	GCD(b, r, gcd, m, n);
	
	int t = *n;
	*n = *m - q * *n;
	*m = t;
}
