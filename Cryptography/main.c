//
//  main.c
//  Cryptography
//
//  Created by Asaf Baibekov on 29/10/2022.
//

#include <stdio.h>
#include "gcd.h"
#include "inverse.h"
#include "crt.h"

int main(int argc, const char * argv[]) {
	printf("======================================\n");
	int a, b;
	scan_for_gcd(&a, &b);
	print_gcd(a, b);
	printf("======================================\n");
	scan_for_inverse(&a, &b);
	print_inverse(a, b);
	printf("======================================\n");
	print_demo_crt();
	printf("======================================\n");
	return 0;
}
