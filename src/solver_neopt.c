/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");
	int i, j, k;

	// AUX_1 = B * A
	double *AUX_1 = (double *) calloc(N * N, sizeof(double));
	if (!AUX_1) {
		return NULL;
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k <= j; k++) {
				AUX_1[i * N + j] += B[i * N + k] * A[k * N + j];
			}
		}
	}

	// AUX_2 = AUX_1 * A' = B * A * A'
	double *AUX_2 = (double *) calloc(N * N, sizeof(double));
	if (!AUX_2) {
		return NULL;
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = j; k < N; k++) {
				AUX_2[i * N + j] += AUX_1[i * N + k] * A[j * N + k];
			}
		}
	}

	free(AUX_1);

	// AUX_3 = B' * B
	double *AUX_3 = (double *) calloc(N * N, sizeof(double));
	if (!AUX_3) {
		return NULL;
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < N; k++) {
				AUX_3[i * N + j] += B[k * N + i] * B[k * N + j];
			}
		}
	}

	// AUX_2 will now be AUX_2 + AUX_3 = B * A * A' + B' * B
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			AUX_2[i * N + j] += AUX_3[i * N + j];
		}
	}

	free(AUX_3);

	return AUX_2;
}
