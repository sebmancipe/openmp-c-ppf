#include <stdio.h>
#include <omp.h>

int main() {
    avg_reduction();
    return 0;
}

void avg_round_robin() {
    int N = 600000000;
    double tavg = 0;

    double timer_start = omp_get_wtime();
    omp_set_num_threads(16);
    #pragma omp parallel
    {
        double avg;
        int id = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        for (int i = id; i < N; i+=nthreads) {
            avg += i;
        }
        #pragma omp atomic
        tavg += avg;
    }
    double timer_elapsed = omp_get_wtime() - timer_start;
    tavg = tavg / N;

    printf("%f took %f\n", tavg, timer_elapsed);
}


void avg_reduction() {
    int N = 20;
    int j = 0;
    double tavg = 0;

    double timer_start = omp_get_wtime();

    #pragma omp parallel for reduction(+:tavg)
        for (j = 0; j < N; ++j) {
            tavg += j;
        }

    double timer_elapsed = omp_get_wtime() - timer_start;
    tavg = tavg / N;

    printf("%f took %f\n", tavg, timer_elapsed);
}