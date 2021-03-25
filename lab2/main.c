#include <stdio.h>
#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>

int main() {
	
	// variables
	
	FILE *fp;
	
	int signum;	
	int n = 4;
	int i = 0, j = 0, k = 0;
	
	float det_a;
	
	gsl_matrix *a = gsl_matrix_calloc(n, n);
	gsl_matrix *a_copy = gsl_matrix_calloc(n, n);
	gsl_matrix *a_odwr = gsl_matrix_calloc(n, n);
	gsl_matrix *c = gsl_matrix_calloc(n, n);
	
	gsl_vector *b = gsl_vector_calloc(n);
	
	gsl_vector *x1 = gsl_vector_calloc(n);
	gsl_vector *x2 = gsl_vector_calloc(n);
	gsl_vector *x3 = gsl_vector_calloc(n);
	gsl_vector *x4 = gsl_vector_calloc(n);
	
	gsl_permutation *p = gsl_permutation_alloc(n);
	
	//
	
	fp = fopen("wynik.dat", "w");
	
	//
	
	printf("Macierz a\n");
	fprintf(fp, "Macierz a\n");
	
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			gsl_matrix_set(a, i, j, 1.0/(i+j+2));
			gsl_matrix_set(a_copy, i, j, gsl_matrix_get(a, i, j));
			fprintf(fp, "%f ", gsl_matrix_get(a, i, j));
			printf("%f ", gsl_matrix_get(a, i, j));
		}
		printf("\n");
		fprintf(fp, "\n");
	}
	
	printf("\n");
	fprintf(fp, "\n");
	
	//
	
	gsl_linalg_LU_decomp(a, p, &signum);
	
	//
	// koniec 1 //
	//
	
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			printf("%f ", gsl_matrix_get(a, i, j));
		}
		printf("\n");
	}
	
	//
	
	det_a = 1;
	
	//
	
	fprintf(fp, "Elementy diagonalne U\n");
	
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			if(i == j) {
				fprintf(fp, "%f ", gsl_matrix_get(a, i, j));
				det_a *= gsl_matrix_get(a, i, j);
			}
		}
	}
	
	printf("\nwyznacznik macierzy a\n%g\n", det_a);
	
	fprintf(fp, "\n\nwyznacznik macierzy a\n%g\n", det_a);
	
	//
	// koniec 2 //
	//
	
	gsl_vector_set_zero(b);
	gsl_vector_set(b, 0, 1);
	gsl_linalg_LU_solve(a ,p, b, x1);
	
	gsl_vector_set_zero(b);
	gsl_vector_set(b, 1, 1);
	gsl_linalg_LU_solve(a ,p, b, x2);
	
	gsl_vector_set_zero(b);
	gsl_vector_set(b, 2, 1);
	gsl_linalg_LU_solve(a ,p, b, x3);
	
	gsl_vector_set_zero(b);
	gsl_vector_set(b, 3, 1);
	gsl_linalg_LU_solve(a ,p, b, x4);
	
	//
	
	printf("\nmacierz odwrotna a^-1:\n");
	fprintf(fp, "\nmacierz odwrotna a^-1\n");
	for(i = 0; i < n; i++) {
		printf("%f	", gsl_vector_get(x1, i));
		fprintf(fp, "%f	", gsl_vector_get(x1, i));
		
		printf("%f	", gsl_vector_get(x2, i));
		fprintf(fp, "%f	", gsl_vector_get(x2, i));
		
		printf("%f	", gsl_vector_get(x3, i));
		fprintf(fp, "%f	", gsl_vector_get(x3, i));
		
		printf("%f\n", gsl_vector_get(x4, i));
		fprintf(fp, "%f\n", gsl_vector_get(x4, i));
	}
	
	for(i = 0; i < n; i++) {
		gsl_matrix_set(a_odwr, 0, i, gsl_vector_get(x1, i));
		gsl_matrix_set(a_odwr, 1, i, gsl_vector_get(x2, i));
		gsl_matrix_set(a_odwr, 2, i, gsl_vector_get(x3, i));
		gsl_matrix_set(a_odwr, 3, i, gsl_vector_get(x4, i));
	}
	
	//
	// koniec 3 //
	//
	
	fprintf(fp, "\nIloczyn a * a^-1:\n");
	printf("\nIloczyn a * a^-1:\n");
	
	// wartosci sa wyzerowane przy alokacji
	
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			for(k = 0; k < n; k++) {
				gsl_matrix_set(c, i, j, gsl_matrix_get(c, i, j) + gsl_matrix_get(a_copy, i, k) * gsl_matrix_get(a_odwr, k, j));
			}
			fprintf(fp, "%g	", gsl_matrix_get(c, i, j));
			printf("%g	", gsl_matrix_get(c, i, j));
		}
		printf("\n");
		fprintf(fp, "\n");
	}
	
	//
	// koniec 4 //
	//
	
	
	
	//
	
	return 0;
}
