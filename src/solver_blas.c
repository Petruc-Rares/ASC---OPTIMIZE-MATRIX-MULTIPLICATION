/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#include <cblas.h>
/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");
	double *C = (double *) calloc(N * N, sizeof(double));
	if (!C) {
		printf("Error in allocating C");
		return C;
	}

	// C = 1 * B' * B + 0 * C;
	// C = B' * B
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, N, N,
		N, 1, B, N, B, N, 0, C, N);

	// A = A * A'
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans,
				CblasNonUnit, N, N, 1, A, N, A, N);

	// C = 1 * B * A + 1 * C
	// C = B * A * A' + B' * B
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N,
				1, B, N, A, N, 1, C, N);

	return C;
}
