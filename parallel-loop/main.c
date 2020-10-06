#include <stdio.h>
#include <omp.h>

int main() {
    printf("Loop starting...\n");

    #pragma omp parallel for
    for (int i = 0; i < 10; ++i) {
        printf("%d",i);
    }
    printf("\nLoop ending...\n");
//    Expected output will be similar to this:
//    the begin of loop
//    6378049152
//    the end of loop
    return 0;
}