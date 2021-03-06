/*
* Author of C++ script: Mustafa Atik - muatik@gmail.com 
* Authors of C script: 
*   Anderson Ballesteros - anderson.ballesteros@correo.usa.edu.co 
*   Sebastian Mancipe - sebastian.mancipe@correo.usa.edu.co
* Sergio Arboleda University
* Bogota, Colombia
* 2020
*/

#include <stdio.h>
#include <omp.h>

int main() {
    avg_reduction();
    return 0;
}


// Esta funcion explica explisitamente cómo trabaja la funcion reduction de omp
void avg_round_robin() {
    int N = 600000000;
    // int N = 20;
    double tavg = 0;

    double timer_start = omp_get_wtime();
    // omp_set_num_threads(16);
    omp_set_num_threads(5);

    // Inicia la explicacion de la función reduction
    #pragma omp parallel // Inicio de zona paralela
    {
        double avg; // Variable privada para cada hilo. Esta variable almacenará los valores finales en cada hilp
        int id = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        for (int i = id; i < N; i+=nthreads) { // asignación de la distribución de trabajo para cada hilo. Ej: Nthreads=4; thread0=(0, 4, 8...); thread3=(3, 7, 11...) 
            avg += i;
            // printf("thread: %d, %.2f\n", id, avg);
        }
        #pragma omp atomic
        tavg += avg; // Al finalizar la ejecución de cada hilo, su valor final se agrega a la variable global
    }
// finaliza la explicación de la función reduction

    double timer_elapsed = omp_get_wtime() - timer_start;
    tavg = tavg / N;

    printf("%f took %f\n", tavg, timer_elapsed);
}

void avg_reduction() {
    int N = 600000000;
    // int N = 20;
    int j = 0;
    double tavg = 0;

    double timer_start = omp_get_wtime();
    omp_set_num_threads(48);
    // omp_set_num_threads(5);

    // Explicación detallada en la función avg_round_robin() 
    #pragma omp parallel for reduction(+:tavg)
        for (j = 0; j < N; ++j) {
            tavg += j;
            // printf("thread: %d, %.2f\n", omp_get_thread_num(), tavg);
        }

    double timer_elapsed = omp_get_wtime() - timer_start;
    tavg = tavg / N;

    printf("%f took %f\n", tavg, timer_elapsed);
}