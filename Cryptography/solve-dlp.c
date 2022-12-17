//
//  solve-dlp.c
//  Cryptography
//
//  Created by Asaf Baibekov on 16/12/2022.
//

#include "solve-dlp.h"

// space complexity - O(√p)
long long *BSGS_solve(int g, int y, int p) {
	int m = sqrt(p);
	long long *inv = inverse(g, p);
	
	if (inv == NULL) return NULL;
	long long e = exponent(*inv, m, p);
	free(inv);
	
	long long *baby_array = malloc(sizeof(long long) * m);
	long long *giant_array = malloc(sizeof(long long) * m);
	
	for (int i = 0; i < m; i++) {
		baby_array[i] = exponent(g, i, p);
		giant_array[i] = (y * exponent(e, i, p)) % p;
	}
	
	for (int i = 0; i < m; i++) {
		long long giant_element = giant_array[i];
		for (int j = 0; j < m; j++) {
			if (giant_element == baby_array[j]) {
				long long *toRet = malloc(sizeof(long long));
				*toRet = m * i + j;
				return toRet;
			}
		}
	}
	return NULL;
}

long long *linearCongruence(long long a, long long b, long long m, long long *size) {
	a %= m;
	b %= m;

	long long u, v;
	extended_gcd(a, m, size, &u, &v);

	if (b % *size != 0) {
		*size = 0;
		return malloc(sizeof(long long) * *size);
	}

	long long x = (u * (b / *size)) % m;
	if (x < 0) x += m;

	long long *toRet = malloc(sizeof(long long) * *size);
	for (long long i = 0; i <= *size - 1; i++)
		toRet[i] = (x + i * (m / *size)) % m;
	return toRet;
}

void update(long long r, long long *a, long long *b) {
	switch(r % 3) {
		case 0: (*a)++; break;
		case 1: (*b)++; break;
		case 2:
			*a *= 2;
			*b *= 2;
			break;
	}
}

// space comlexity - O(1)
long long *pollard_solve(int g, int y, int p) {
	long long a1 = 1;
	long long b1 = 1;
	
	long long a2 = 1;
	long long b2 = 1;
	
	long long r1 = 0;
	long long r2 = 0;
	
	bool isFirstTime = true;
	while (r1 != r2 || isFirstTime) {
		r1 = (exponent(g, a1, p) * exponent(y, b1, p)) % p;
		update(r1, &a1, &b1);
		
		r2 = (exponent(g, a2, p) * exponent(y, b2, p)) % p;
		update(r2, &a2, &b2);
		
		r2 = (exponent(g, a2, p) * exponent(y, b2, p)) % p;
		update(r2, &a2, &b2);
		
		isFirstTime = false;
	}
	
	long long B = b2 - b1;
	long long A = a1 - a2;
	if (A < 0)
		A += p - 1;
	long long size;
	
	// Bx === A mod (p - 1)
	long long *solutions = linearCongruence(B, A, p - 1, &size);
	for (int i = 0; i < size; i++) {
		if (exponent(g, solutions[i], p) == y) {
			long long *toRet = malloc(sizeof(long long));
			*toRet = solutions[i];
			free(solutions);
			return toRet;
		}
	}
	return NULL;
}
