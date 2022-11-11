//
//  square-and-multiply.c
//  Cryptography
//
//  Created by Asaf Baibekov on 11/11/2022.
//

#include "square-and-multiply.h"

void print_for_exponent(int x, int e, int p) {
	int result = exponent(x, e, p);
	printf("%d^%d (mod %d) === %d\n", x, e, p, result);
}

char *decimal_to_binary_string(int decimal) {
	int bin = 0;
	int rem, i = 1;
	while (decimal != 0) {
		rem = decimal % 2;
		decimal /= 2;
		bin += rem * i;
		i *= 10;
	}
	int count = 0;
	int temp = bin;
	while (temp > 0) {
		count++;
		temp /= 10;
	}
	char *str = malloc(sizeof(char) * (count + 1));
	sprintf(str, "%d", bin);
	return str;
}

// x^e (mod p)
unsigned int exponent(int x, int e, int p) {
	unsigned int result = x;
	char *binary = decimal_to_binary_string(e);
	size_t bin_digit_size = strlen(binary);
	for (int i = 1; i < bin_digit_size; i++) {
		char digit = binary[i];
		result *= result; // result = result^2; <-> result = result * result;
		result %= p; // result = result % p;
		if (digit == '1') {
			result *= x; // result = result * x;
			result %= p; // result = result % p;
		}
	}
	free(binary);
	return result;
}
