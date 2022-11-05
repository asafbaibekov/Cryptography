//
//  main.c
//  Cryptography
//
//  Created by Asaf Baibekov on 29/10/2022.
//

#include <stdio.h>
#include "gcd.h"

int main(int argc, const char * argv[]) {
	int a, b;
	scan_for_gcd(&a, &b);
	print_gcd(a, b);
	printf("\n");
	return 0;
}
