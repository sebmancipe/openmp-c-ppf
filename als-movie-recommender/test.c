#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void sumEscalarVector(float escalar, int *v, int size, int *result) {
   
}

int main(int argc, char ** argv) {
    int *g = (int *)calloc(1, sizeof(int *));
    int i;
    for (i = 0; i <6 ; i++) {
        g[i] = 1;
    }
    // printf("%d, %d\n", i-1, g[i-1]);
    // printf("%d, %d\n", 1, g[1]);

    realloc(g, 7*sizeof(int *));
    g[6] = 5;
    printf("%d, %d\n", 6, g[6]);
    printf("%d, %d\n", 1, g[1]);
    
}


