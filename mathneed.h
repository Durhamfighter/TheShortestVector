#ifndef MATHNEED_H
#define MATHNEED_H

struct Vector{
    double *components;
};
double inner_product(double *u, double *v, int dim); //math
void project(double *v, double *u, double *projection, int dim); //maht but dont need it

#endif
