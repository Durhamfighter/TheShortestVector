#include "mathneed.h"
#include "gram.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Vector *gramSchmidt(struct Vector *basis, int dim) {
    struct Vector *U;
    U = (struct Vector *)malloc(dim*sizeof(struct Vector));
    double *proj = (double *)malloc(dim * sizeof(double));
    if (proj == NULL) {
        fprintf(stderr, "Memory allocation failed for U\n");
        return NULL;
    }
    if (U == NULL) {
        fprintf(stderr, "Memory allocation failed for U\n");
        return NULL;
    }
    for (int i = 0; i < dim; i++) {
        U[i].components = (double *)malloc(dim * sizeof(double));
        if (U[i].components == NULL) {
           printf("Memory allocation failed for U[%d].components\n", i);
            for (int j = 0; j < i; j++) {
                free(U[j].components);
            }
            free(U);
            return NULL;
        }
    }
    for (int i = 0; i < dim; i++) {
        memcpy(U[i].components, basis[i].components, dim * sizeof(double));
        for (int j = 0; j < i; j++) {
            project(U[i].components, U[j].components, proj, dim);
            for (int k = 0; k < dim; k++) {
                U[i].components[k] -= proj[k];  //  Subtract the projection
            }
        }
}
    free(proj);
    return U;
}
double **mu_generate(struct Vector *v, struct Vector *u, int dim) {
    double **mu = malloc(dim * sizeof(double*));
    if (mu == NULL) {
    fprintf(stderr, "Error allocating memory from mu\n");
    return NULL;
}
    for (int i = 0; i < dim; i++) {
        mu[i] = malloc((i+1)* sizeof(double));
        if (mu[i] == NULL) {
        fprintf(stderr, "Error allocating memory for row %d\n", i);
        for (int j = 0; j < i; j++) {
            free(mu[j]);
        }
        free(mu);
        return NULL;
        }
        for (int j = 0; j <= i; j++) {
            if (j < i) {
            mu[i][j] = inner_product(v[i].components, u[j].components, dim) /
                        inner_product(u[j].components, u[j].components, dim);
            } else {
                mu[i][j] = 1;
            }
        }
    }
    return mu;
}
