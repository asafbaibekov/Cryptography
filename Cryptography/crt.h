//
//  crt.h
//  Cryptography
//
//  Created by Asaf Baibekov on 05/11/2022.
//

#ifndef crt_h
#define crt_h

#include <stdio.h>
#include "ModularEquation.h"
#include "inverse.h"

void print_demo_crt(void);

void print_for_crt(ModularEquation *modularEquations[], size_t size);

ModularEquation *crt(ModularEquation *modularEquations[], size_t size);

#endif /* crt_h */
