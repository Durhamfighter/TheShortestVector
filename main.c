#include "mathneed.h"
#include "LLL.h"
#include "gram.h"
#include "SE.h"
#include "writefile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main(int argc, char* argv[]) {
    if (argc <= 1) {
            fprintf(stderr, "Error: No vectors\n");
            return -1;
        }
    //  dimension check
    int dim;
    double sqrt_val = sqrt(argc - 1);
    if (floor(sqrt_val) == sqrt_val) {
        dim = (int)sqrt_val;
    } else {
        printf("Wrong Format : dimension \n");
        return -1;
    }
    //  bracket check[[1] 2] or [123]1 4]
    if (dim >= 2) {
        for (int i = 1; i < argc; i++) {
        char *str = argv[i];
        int open_bracket = 0;
        int close_bracket = 0;
        while (*str != '\0') {
            if (*str == '[') {
                open_bracket++;
            } else if (*str == ']') {
                close_bracket++;
            }
            if (open_bracket > 1 || close_bracket > 1) {
                printf("Wrong format: double bracket\n");
                return -1;
            }
            if (open_bracket == 1 && close_bracket == 1) {
                printf("Wrong format: cases like [123]4 \n");
                return -1;
            }
        str++;
        }
    }
    } else {
        char *str = argv[1];
        int open_bracket = 0;
        int close_bracket = 0;
        while (*str != '\0') {
            if (*str == '[') {
                open_bracket++;
            } else if (*str == ']') {
                close_bracket++;
                char *temp = str;
                temp++;
                if (*temp != '\0') {
                    printf(" one dimension Wrong format: double bracket\n");
                    return -1;
                }
            }
            if (open_bracket > 1 || close_bracket > 1) {
                printf("Wrong format\n");
                return -1;
            }
            str++;
        }
    }
    //  [1 2 3 4] [5 6] [7 8 9] check wrong dimension format.
    int k = 1;
    while (k < argc) {
        int open = 0;
        int close = 0;
        for (int i = 0; i < dim; i++) {
            char *str = argv[k];
                while (*str != '\0') {
                    if (*str == '[') {
                        open++;
                    } else if (*str == ']') {
                        close++;
                    }
                    str++;
                }
                k++;
        }
        if (open != 1 || close != 1) {
            fprintf(stderr,
             "Error : Wrong format : [1 2 3 4] [5 6] [7 8 9] \n");
            return -1;
        }
    }
    struct Vector *basis;
    basis = (struct Vector *)malloc(dim * sizeof(struct Vector));
    if (basis == NULL) {
        fprintf(stderr, "Memory allocation failed for basis\n");
        return -1;
    }
    for (int i=0; i < dim; i++) {
        basis[i].components = (double *)malloc(dim * sizeof(double));
        if (basis[i].components == NULL) {
            printf("Memory allocation failed for basis[%d].components\n", i);
            for (int j = 0; j < i; j++) {
                free(basis[j].components);
            }
            free(basis);  //  Free allocated mnemory so far.
            return -1;
        }
    }
    int j = 0;
    for (int i = 1; i < argc; i++) {
        char *endptr;
        char *token = strtok(argv[i], "[]");
        double ret = strtod(token, &endptr);
         if (*endptr != '\0') {
            printf("Wrong format : [2a] or [-2-] etc \n");
            for (int i = 0; i < dim; i++) {
                free(basis[i].components);
            }
            free(basis);
            return -1;
        }
        basis[j].components[(i-1)%dim] = ret;
        if (i%dim == 0) {
            j++;
        }
    }
    struct Vector *U = gramSchmidt(basis, dim);
    //  independence check
    double epsilon = pow(10, -10);
    for (int i = 1; i < dim; i++) {
        int zero_count = 0;
        for (int j = 0; j < dim; j++) {
            if (fabs(U[i].components[j]) < epsilon) {
                zero_count++;
            }
        }
        if (zero_count == dim) {
            fprintf(stderr, "Input vectors are not independent\n");
            for (int i = 0; i < dim; i++) {
                free(basis[i].components);
                free(U[i].components);
            }
            free(U);
            free(basis);
            return 1;
        }
    }
    double **mu = mu_generate(basis, U, dim);
    if (LLL(basis, U, mu, dim) != 0) {
        return -1;
    }
    double R_squared = lamda_bound(U, dim);
    double *s = SE(basis, U, mu, dim, &R_squared);
    double sum = 0;
        for (int i = 0; i < dim; i++) {
            sum += s[i] * s[i];
        }
    double result = sqrt(sum);
    for (int j = 0; j < dim; j++) {
        free(basis[j].components);
        free(U[j].components);
    }
    free(U);
    free(s);
    free(basis);
    WriteToFile(result);
    return 0;
}
