#include <stdio.h>
#include <stdlib.h>
#include "mathneed.h"
double inner_product(double *v, double *u , int dim) {
    double sum = 0;
    for (int i = 0; i < dim; i++) {
        sum += (v[i] * u[i]);
    }
    //  omit sqrt(sum) as it is not optimal at the moment
    return sum;
}
void project(double *v, double *u, double *projection, int dim) {
    double co = inner_product(v, u, dim) / inner_product(u, u, dim);
    for (int i = 0; i < dim; i++) {
        projection[i] = co * u[i];
    }
}
