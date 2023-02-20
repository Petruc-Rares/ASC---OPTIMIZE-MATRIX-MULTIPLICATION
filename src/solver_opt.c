/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");
	int i, j, k;

	// AUX_1 = B * A
	double *AUX_1 = (double *) calloc(N*N, sizeof(double));
	if (!AUX_1) {
		return NULL;
	}

	for (i = 0; i < N; i++) {
		double *orig_prows = &B[i * N];
		double *orig_result = &AUX_1[i * N];
		for (j = 0; j < N; j++) {
			double *prows = orig_prows;
			double *pcolumns = &A[j];
			register double suma = 0.0;
			for (k = 0; k <= j; k++) {
				suma += *prows * *pcolumns;
				prows++;
				pcolumns += N;
			}
			*orig_result = suma;
			orig_result++;
		}
	}

	// AUX_2 = AUX_1 * A' = B * A * A'
	double *AUX_2 = (double *) calloc(N*N, sizeof(double));
	if (!AUX_2) {
		return NULL;
	}

	for (i = 0; i < N; i++) {
		double *orig_prows = &AUX_1[i * N];
		double *orig_result = &AUX_2[i * N];
		for (j = 0; j < N; j++) {
			double *prows = orig_prows + j;
			double *pcolumns = &A[j * N + j];
			register double suma = 0.0;
			for (k = j; k < N; k++) {
				suma += *prows * *pcolumns;
				prows++;
				pcolumns++;
			}
			*(orig_result + j) = suma;
		}
	}


	free(AUX_1);

	// AUX_3 = B' * B
	double *AUX_3 = (double *) calloc(N*N, sizeof(double));
	if (!AUX_3) {
		return NULL;
	}

	for (i = 0; i < N; i++) {
		double *orig_presult = &AUX_3[i * N];
		for (k = 0; k < N; k++) {
			double *presult = orig_presult;
			double *prows = &B[k * N];
			register double va = *(prows + i);
			for (j = 0; j < N; j++) {
				*presult += va * *prows;
				presult++;
				prows++;
			}
		}
	}

	for (i = 0; i < N; i++) {
		double *paux2 = &AUX_2[i * N];
		double *paux3 = &AUX_3[i * N];
		for (j = 0; j < N; j++) {
			*paux2 += *paux3;
			paux2++;
			paux3++;
		}
	}

	free(AUX_3);

	return AUX_2;
}
