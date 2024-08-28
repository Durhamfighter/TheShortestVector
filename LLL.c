#include "mathneed.h"
#include "LLL.h"
#include "gram.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int LLL(struct Vector *basis, struct Vector *U, double **mu , int dim) {
    double *projection = malloc(dim*sizeof(double));
    if (projection == NULL) {
        fprintf(stderr,
         "Memory allocation failed for projection in LLL function\n");
        for (int i=0; i < dim; i++) {
            free(basis[i].components);
        }
        free(basis);
        return 1;  // Exit the program
    }
    double delta = 0.75;
    //  independence check
    int k = 1;
    while (k < dim) {
        for (int j=k-1; j >= 0; j--) {
            if (fabs(mu[k][j]) > 0.5) {
                for (int i=0; i < dim; i++) {
                    double coef = round(mu[k][j]) * basis[j].components[i];
                   basis[k].components[i] -= coef;
                }
                //  update U and mu
                update_U_mu(basis, U, mu, dim, projection);
            }
        }
        if (inner_product(U[k].components, U[k].components, dim) >
            ((delta - mu[k][k - 1] * mu[k][k - 1]) *
            inner_product(U[k - 1].components, U[k - 1].components, dim))) {
            k = k+1;
        } else {
            //  swap basis[k].components and basis[k-1].components
            double *temp = basis[k].components;
            basis[k].components = basis[k-1].components;
            basis[k-1].components = temp;
            //  update B* and related mu;
            update_U_mu(basis, U, mu, dim, projection);
            if (k-1 > 1) {
                k = k-1;
            } else {
                k = 1;
            }
        }
    }
    free(projection);
    return 0;
}
void update_U_mu(struct Vector *basis, struct Vector *U, double **mu,
                 int dim, double *projection) {
     for (int i = 0; i < dim; i++) {
        memcpy(U[i].components, basis[i].components,
         dim * sizeof(double));
        for (int j=0; j < i; j++) {
            double co = inner_product(U[i].components, U[j].components, dim) /
            inner_product(U[j].components, U[j].components, dim);
            mu[i][j] = co;
            for (int l = 0; l < dim; l++) {
                projection[l] = co * (U[j].components[l]);
            }
            for (int k = 0; k < dim; k++) {
                //  Subtract the projection
                U[i].components[k] -= projection[k];
            }
        }
    }
}
