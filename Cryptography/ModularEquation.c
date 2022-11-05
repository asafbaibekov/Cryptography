//
//  ModularEquation.c
//  Cryptography
//
//  Created by Asaf Baibekov on 05/11/2022.
//

#include "ModularEquation.h"

ModularEquation *initModularEquation(int b, int n) {
	ModularEquation *new = malloc(sizeof(ModularEquation));
	new->b = b;
	new->n = n;
	return new;
}

void printModularEquation(ModularEquation *modularEquation) {
	printf("x === %d (mod %d)\n", modularEquation->b, modularEquation->n);
}
