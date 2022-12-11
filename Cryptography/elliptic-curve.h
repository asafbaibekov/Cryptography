//
//  elliptic-curve.h
//  Cryptography
//
//  Created by Asaf Baibekov on 10/12/2022.
//

#ifndef elliptic_curve_h
#define elliptic_curve_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "inverse.h"

typedef struct EllipticCurve {
	int a;
	int b;
	int m;
} EllipticCurve;

typedef struct EllipticCurvePoint {
	int x;
	int y;
} EllipticCurvePoint;

EllipticCurve *initEllipticCurve(int a, int b, int m);

EllipticCurvePoint *initEllipticCurvePoint(int x, int y);

EllipticCurvePoint *copyEllipticCurvePoint(EllipticCurvePoint *point);

EllipticCurvePoint *add_two_point_on_curve(EllipticCurvePoint *point1, EllipticCurvePoint *point2, EllipticCurve *curve);

bool isPointsEqual(EllipticCurvePoint *point1, EllipticCurvePoint *point2);

void printEllipticCurvePoint(EllipticCurvePoint *point);

#endif /* elliptic_curve_h */
