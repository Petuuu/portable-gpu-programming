// SPDX-FileCopyrightText: 2025 CSC - IT Center for Science Ltd. <www.csc.fi>
//
// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdlib.h>
#include "axpy_helper_functions.h"
#include <time.h>

int main(int argc, char* argv[]) {
    // Array size
    int n = 102400;
    if (argc > 1) {
        n = atoi(argv[1]);
    }
    printf("Array size n = %d\n", n);

    double alpha, *x, *y;
    x = (double*)malloc(n * sizeof(double));
    y = (double*)malloc(n * sizeof(double));

    // Initialization
	clock_t start = clock();
    alpha = 3.0;
	#pragma omp target data map(alloc: x[0:n]) map(from: y[0:n])
	{
		#pragma omp target teams distribute parallel for
		for (int i = 0; i < n; i++) {
    	    double frac = 1.0 / ((double) (n - 1));
        	x[i] = i * frac;
    	    y[i] = i * frac * 100;
   		}

		// Print input values
    	printf("Input:\n");
    	printf("a = %8.4f\n", alpha);
		#pragma omp target update map(from: x[0:n]) map(from: y[0:n])
    	print_array("x", x, n);
    	print_array("y", y, n);

    	// Calculate axpy
		#pragma omp target teams distribute parallel for
		for (int i = 0; i < n; i++) {
    		y[i] += alpha * x[i];
		}
		clock_t end = clock();

    	// Print output values
    	printf("Output:\n");
    	print_array("y", y, n);
		printf("Time taken: %.6f\n", (double)(end - start) / (double)CLOCKS_PER_SEC);
	}

    free(y);
    free(x);

    return 0;
}
