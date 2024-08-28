#ifndef SE_H  // Header guard start
#define SE_H
#include "mathneed.h" 
double *SE(struct Vector *b, struct Vector *U, double **mu, int dim, double *R_squared);
double lamda_bound(struct Vector *U, int dim);
#endif