//
//  crt.c
//  Cryptography
//
//  Created by Asaf Baibekov on 05/11/2022.
//

#include "crt.h"

void print_demo_crt(void) {
	printf("run crt demo:\n");
	size_t size = 3;
	ModularEquation **modularEquations = malloc(sizeof(ModularEquation *) * size);
	modularEquations[0] = initModularEquation(2, 5);
	modularEquations[1] = initModularEquation(3, 7);
	modularEquations[2] = initModularEquation(10, 11);
	print_for_crt(modularEquations, size);
	printf("answer: ");
	ModularEquation *finalModularEquation = crt(modularEquations, size);
	if (finalModularEquation == NULL) {
		printf("Couldn't find the answer because inverse is not found,\n");
		printf("Check the equations and try again.\n");
	} else
		printModularEquation(finalModularEquation);
}

void print_for_crt(ModularEquation *modularEquations[], size_t size) {
	for (int i = 0; i < size; i++)
		printModularEquation(modularEquations[i]);
}

ModularEquation *crt(ModularEquation *modularEquations[], size_t size) {
	int N = 1;
	int bnx_sum = 0;
	for (int i = 0; i < size; i++)
		N *= modularEquations[i]->n;
	for (int i = 0; i < size; i++) {
		int n_i = N / modularEquations[i]->n;
		int64_t *x_i = inverse(n_i, modularEquations[i]->n);
		if (x_i == NULL) return NULL;
		bnx_sum += modularEquations[i]->b * n_i * (*x_i);
		free(x_i);
	}
	return initModularEquation(bnx_sum % N, N);
}
