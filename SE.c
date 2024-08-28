#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "SE.h"
#include "mathneed.h"
#include "LLL.h"
double *SE(struct Vector *b, struct Vector *U, double **mu,
           int dim, double *R_squared) {
    //  orthonormal basis and GS information
    double *s = malloc(dim * sizeof(double));
    if (s == NULL) {
        fprintf(stderr, "Memory allocation failed for s\n");
        return NULL;
    }
    //  rho, v, c, w
    double *rho = calloc(dim+1, sizeof(double));
    if (rho == NULL) {
        fprintf(stderr, "Memory allocation failed for rho\n");
        return NULL;
    }
    double *v = calloc(dim, sizeof(double));
    if (v == NULL) {
        fprintf(stderr, "Memory allocation failed for v\n");
        return NULL;
    }
    v[0] = 1;
    double *c = calloc(dim, sizeof(double));
    if (c == NULL) {
        fprintf(stderr, "Memory allocation failed for c\n");
        return NULL;
    }
    double *w = calloc(dim, sizeof(double));
    if (w == NULL) {
        fprintf(stderr, "Memory allocation failed for w\n");
        return NULL;
    }
    double *info_ip = malloc(dim * sizeof(double));
    if (info_ip == NULL) {
        fprintf(stderr, "Memory allocation failed for infor_ip\n");
        return NULL;
    }
    //  optimization for inner product call.
    for (int i = 0; i < dim; i++) {
        info_ip[i] = inner_product(U[i].components, U[i].components, dim);
    }
    int k = 0; int last_nonzero = 0;
    while (1) {
        rho[k] = rho[k+1] + (v[k]-c[k]) * (v[k]-c[k]) * info_ip[k];
        if (rho[k] < *R_squared) {
            if (k == 0) {
                *R_squared = rho[k];
                for (int i = 0; i < dim; i++) {
                    double new = 0;
                    for (int j = 0; j < dim; j++) {
                        new += (b[j].components[i]) * v[j];
                    }
                    s[i] = new;
                }
            } else {
                k = k-1;
                double sum = 0;
                for (int i = k+1; i < dim; i++) {
                    sum += mu[i][k] * v[i];
                }
                c[k] = -sum;
                v[k] = round(c[k]);
                w[k] = 1;
            }
        } else {
            k = k+1;  // going up the tree
            if (k == dim) {
                for (int i = 0; i < dim; i++) {
                    free(mu[i]);
                }
                free(mu);
                free(rho);
                free(v);
                free(c);
                free(w);
                free(info_ip);
                return s;
            }
            if (k >= last_nonzero) {
                last_nonzero = k;
                v[k] = v[k]+1;
            } else {
                if (v[k] > c[k]) {
                    v[k] = v[k] - w[k];
                } else {
                    v[k]= v[k] + w[k];
                }
                w[k] = w[k] + 1;
            }
        }
    }
}
double lamda_bound(struct Vector *U, int dim) {
    double sum = 1;
    for (int i = 0; i < dim; i++) {
        sum *= inner_product(U[i].components, U[i].components, dim);
    }
    double result = (1.0/dim);
    sum = pow(sum, result);
    double con = 1 + (dim * 0.25);
    sum *= con;
    return sum;
}
