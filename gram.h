#ifndef GRAM_H
#define GRAM_H
#include "mathneed.h"
struct Vector *gramSchmidt(struct Vector *basis, int dim); 
double **mu_generate(struct Vector *v, struct Vector *u, int dim);
#endif
