//
//  solve-dlp.h
//  Cryptography
//
//  Created by Asaf Baibekov on 16/12/2022.
//

#ifndef solve_dlp_h
#define solve_dlp_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include "square-and-multiply.h"
#include "inverse.h"

int64_t *linearCongruence(int64_t a, int64_t b, int64_t n, int64_t *size);

uint64_t *BSGS_solve(int g, int y, int p);

int64_t *pollard_solve(int g, int y, int p);

#endif /* solve_dlp_h */
