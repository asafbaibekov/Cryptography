//
//  ModularEquation.c
//  Cryptography
//
//  Created by Asaf Baibekov on 05/11/2022.
//

#include "ModularEquation.h"

ModularEquation *initModularEquation(uint64_t b, uint64_t n) {
	ModularEquation *new = malloc(sizeof(ModularEquation));
	new->b = b;
	new->n = n;
	return new;
}

void printModularEquation(ModularEquation *modularEquation) {
	printf("x === %lld (mod %lld)\n", modularEquation->b, modularEquation->n);
}
