//
//  ModularEquation.h
//  Cryptography
//
//  Created by Asaf Baibekov on 05/11/2022.
//

#ifndef ModularEquation_h
#define ModularEquation_h

#include <stdio.h>
#include <stdlib.h>

typedef struct ModularEquation {
	// x === b (mod n)
	uint64_t b;
	uint64_t n;
} ModularEquation;

ModularEquation *initModularEquation(uint64_t b, uint64_t n);

void printModularEquation(ModularEquation *modularEquation);

#endif /* ModularEquation_h */
