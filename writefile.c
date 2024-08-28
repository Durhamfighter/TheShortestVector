#include "writefile.h"
#include <stdio.h>
#include <stdlib.h>
void WriteToFile(double s) {
    FILE *ofp;
    ofp = fopen("result.txt", "w");
    if (ofp == NULL) {
       fprintf(stderr, "Unable to open file!");
       EXIT_FAILURE;
    }
    fprintf(ofp, "%8.8f", s);
    fclose(ofp);
}
