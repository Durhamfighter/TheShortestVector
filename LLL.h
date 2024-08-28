#ifndef LLL_H
#define LLL_H
#include "mathneed.h"
int LLL(struct Vector *basis, struct Vector *U, double **mu , int dim);
void update_U_mu(struct Vector *basis, struct Vector *U, double **mu, int dim, double *projection);
#endif
