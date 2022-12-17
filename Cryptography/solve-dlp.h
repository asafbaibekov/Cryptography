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
#include <math.h>
#include <stdbool.h>
#include "square-and-multiply.h"
#include "inverse.h"

long long *linearCongruence(long long a, long long b, long long n, long long *size);

long long *BSGS_solve(int g, int y, int p);

long long *pollard_solve(int g, int y, int p);

#endif /* solve_dlp_h */
