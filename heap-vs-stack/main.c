
#include <stdio.h>
#include <omp.h>

int main() {
    
    int heap_sum = 0; // variable compartida
    omp_set_num_threads(3);
    #pragma omp parallel
    {
        int stack_sum=0; // variable privada
        stack_sum++;
        heap_sum++; // Sumarle 1 a la variable compartida, 
                    //sin embargo al acceder a ella paralelamente, esto se puede corromper 
        printf("stack sum is %d\n", stack_sum);
        printf("heap sum is %d\n", heap_sum);
    }
    printf("final heap sum is %d\n", heap_sum);
    return 0;
}