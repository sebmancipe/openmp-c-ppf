
#include <stdio.h>
#include <omp.h>

int main() {
    
    int heap_sum = 0;
    omp_set_num_threads(3);
    #pragma omp parallel
    {
        int stack_sum=0;
        stack_sum++;
        heap_sum++;
        printf("stack sum is %d\n", stack_sum);
        printf("heap sum is %d\n", heap_sum);
    }
    printf("final heap sum is %d\n", heap_sum);
    return 0;
}