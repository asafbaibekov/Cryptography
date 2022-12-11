//
//  elliptic-curve.c
//  Cryptography
//
//  Created by Asaf Baibekov on 10/12/2022.
//

#include "elliptic-curve.h"

EllipticCurve *initEllipticCurve(int a, int b, int m) {
	EllipticCurve *new = malloc(sizeof(EllipticCurve));
	new->a = a;
	new->b = b;
	new->m = m;
	return new;
}

EllipticCurvePoint *initEllipticCurvePoint(int x, int y) {
	EllipticCurvePoint *new = malloc(sizeof(EllipticCurvePoint));
	new->x = x;
	new->y = y;
	return new;
}

EllipticCurvePoint *copyEllipticCurvePoint(EllipticCurvePoint *point) {
	if (point == NULL) return NULL;
	EllipticCurvePoint *new = malloc(sizeof(EllipticCurvePoint));
	new->x = point->x;
	new->y = point->y;
	return new;
}

EllipticCurvePoint *add_two_point_on_curve(EllipticCurvePoint *point1, EllipticCurvePoint *point2, EllipticCurve *curve) {
	if (point1 == NULL && point2 == NULL)
		return NULL;
	else if (point1 == NULL)
		return copyEllipticCurvePoint(point2);
	else if (point2 == NULL)
		return copyEllipticCurvePoint(point1);
	
	int s_numerator = 0;
	int s_denominator = 0;
	if (isPointsEqual(point1, point2)) {
		s_numerator = (3 * ((int) pow(point1->x, 2)) + curve->a) % curve->m;
		s_denominator = (2 * point1->y) % curve->m;
	} else {
		s_numerator = (point2->y - point1->y) % curve->m;
		s_denominator = (point2->x - point1->x) % curve->m;
	}
	if (s_numerator < 0) s_numerator += curve->m;
	if (s_denominator < 0) s_denominator += curve->m;
	
	if (s_denominator == 0) return NULL;
	
	if (s_numerator == 0) {
		int s = 0;
		int x = (((int) pow(s, 2)) - point1->x - point2->x) % curve->m;
		int y = (s * (point1->x - x) - point1->y) % curve->m;
		if (x < 0) x += curve->m;
		if (y < 0) y += curve->m;
		return initEllipticCurvePoint(x, y);
	} else {
		long long *inv = inverse(s_denominator, curve->m);
		if (inv == NULL) return NULL;
		int s = (s_numerator * *inv) % curve->m;
		int x = (((int) pow(s, 2)) - point1->x - point2->x) % curve->m;
		int y = (s * (point1->x - x) - point1->y) % curve->m;
		if (x < 0) x += curve->m;
		if (y < 0) y += curve->m;
		free(inv);
		return initEllipticCurvePoint(x, y);
	}
}

bool isPointsEqual(EllipticCurvePoint *point1, EllipticCurvePoint *point2) {
	return point1->x == point2->x && point1->y == point2->y;
}

void printEllipticCurvePoint(EllipticCurvePoint *point) {
	if (point == NULL)
		printf("(0, 0)");
	else
		printf("(%d, %d)", point->x, point->y);
}
