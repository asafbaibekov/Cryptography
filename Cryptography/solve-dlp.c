//
//  solve-dlp.c
//  Cryptography
//
//  Created by Asaf Baibekov on 16/12/2022.
//

#include "solve-dlp.h"

// space complexity - O(√p)
uint64_t *BSGS_solve(int g, int y, int p) {
	int m = sqrt(p);
	int64_t *inv = inverse(g, p);
	
	if (inv == NULL) return NULL;
	uint64_t e = exponent(*inv, m, p);
	free(inv);
	
	uint64_t *baby_array = malloc(sizeof(uint64_t) * m);
	uint64_t *giant_array = malloc(sizeof(uint64_t) * m);
	
	for (int i = 0; i < m; i++) {
		baby_array[i] = exponent(g, i, p);
		giant_array[i] = (y * exponent(e, i, p)) % p;
	}
	
	for (int i = 0; i < m; i++) {
		uint64_t giant_element = giant_array[i];
		for (int j = 0; j < m; j++) {
			if (giant_element == baby_array[j]) {
				uint64_t *toRet = malloc(sizeof(uint64_t));
				*toRet = m * i + j;
				return toRet;
			}
		}
	}
	return NULL;
}

int64_t *linearCongruence(int64_t a, int64_t b, int64_t m, int64_t *size) {
	a %= m;
	b %= m;

	int64_t u, v;
	extended_gcd(a, m, size, &u, &v);

	if (b % *size != 0) {
		*size = 0;
		return malloc(sizeof(int64_t) * *size);
	}

	int64_t x = (u * (b / *size)) % m;
	if (x < 0) x += m;

	int64_t *toRet = malloc(sizeof(int64_t) * *size);
	for (int64_t i = 0; i <= *size - 1; i++)
		toRet[i] = (x + i * (m / *size)) % m;
	return toRet;
}

void update(int64_t r, int64_t *a, int64_t *b) {
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
int64_t *pollard_solve(int g, int y, int p) {
	int64_t a1 = 1;
	int64_t b1 = 1;
	
	int64_t a2 = 1;
	int64_t b2 = 1;
	
	int64_t r1 = 0;
	int64_t r2 = 0;
	
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
	
	int64_t B = b2 - b1;
	int64_t A = a1 - a2;
	if (A < 0)
		A += p - 1;
	int64_t size;
	
	// Bx === A mod (p - 1)
	int64_t *solutions = linearCongruence(B, A, p - 1, &size);
	for (int i = 0; i < size; i++) {
		if (exponent(g, solutions[i], p) == y) {
			int64_t *toRet = malloc(sizeof(int64_t));
			*toRet = solutions[i];
			free(solutions);
			return toRet;
		}
	}
	return NULL;
}
