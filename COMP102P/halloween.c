#include<stdio.h>

// A recursive function that accepts an array of integers
// and length and returns the highest common divisor of them.
int hcd(int *vals, int length) {
	if (length==2) {
		// HCD of two numbers using euclid's algorithm.
		int m,n;
		m = vals[0];
		n = vals[1];
		while (m > 0) {
			int temp = m;
			m = n % m;
			n = temp;
		}
		return n;
	}
	else if (length > 2) {
		// using identity that hcd(a,b,c,..) = hcd(a,hcd(b,c,..))
		int vals2[2];
		vals2[0]=vals[0];
		// hcd of tail of array.
		vals2[1]=hcd((vals + 1),length-1);
		// finally, hcd of result of hcd and head of array.
		return hcd(vals2,2);
	}
	// There was an error.
	else return -1;
}

int main(int argc, char *argv[]) {
	// Don't make me laugh.
	if (argc<=2) {
		return 1;
	}
	else {
		int highest, i;
		int *nums;
		// nums is an array of the values to process.
		nums = (int*)calloc(argc-1,sizeof(int));
		
		// let's populate the nums array.
		for (i = 1; i < argc; i++) {
			*(nums + i - 1) = atoi(argv[i]);
		}

		// highest = number of bags.
		highest = hcd(nums,argc-1);

		// (if we didn't mess up somewhere)
		if( highest>0) {
			int i, n, sum;
			// sum: number of sweets per bag.
			sum = 0;
			n = argc - 1;
		   	for (i=0; i < n; i++) {
				sum += nums[i] / highest;
			}
			// there you go.
			printf("%i %i\n",highest,sum);
		}
		else return 1;
	}

	return 0;
}
