// CREATED BY MATTHEW BELL
// This program calculates from input of quantities of various kinds of sweets:
// 1) Maximum number of bags that can be created, and
// 2) Total number of sweets in each bag;
// Subject to the conditions that:
// 1) All bags contain the same number of each kind of sweet,
// 2) The maximum number of bags of sweets are obtained,
// 3) No sweets are left over.
//
// The inputs are given as:
// 1) Number of hard boiled sweets,
// 2) Number of chocolates,
// 3) Number of lollipops,
// 4) Number of marzipans,
// 5) Number of bubble gums.

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int quantities[5];

// int * hcd (int n, int m);
// 
// int * ahcd (int *comparators) {
// 	int n = sizeof(comparators)/sizeof(comparators[0]);
// 
// 	for (int i = 0; i < n; i++) {
// 		printf("%i, ", *(comparators + i));
// 	}
// 	printf("\n");
// 
// 	if (n > 2) {
// 		int *tailHcds = ahcd( (*(comparators) + 1)* );
// 		//then compare list with with array tailHcds.
// 	}
// 	else if (n == 2) {
// 		hcd( *(comparators), *(comparators + 1));
// 	}
// 	else if (n == 1) {
// 		return *(comparators);
// 	}
// 
// }

int main (int argc, char *argv[]) {
	argc--;

	if (argc > 5) {
		return EINVAL;
	}
	if (argc <= 1) {
		return EINVAL;
	}
	if (argc >= 2) {
		quantities[0] = atoi(argv[1]);
		quantities[1] = atoi(argv[2]);
	}
	if (argc >= 3) {
		quantities[2] = atoi(argv[3]);
	}
	if (argc >= 4) {
		quantities[3] = atoi(argv[4]);
	}
	if (argc == 5) {
		quantities[4] = atoi(argv[5]);
	}
	
	int *hcds = hcd(quantities);
	//then get the highest.
}
