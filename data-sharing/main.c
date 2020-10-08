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

void compare_cases();

double G = 2.1;

int main() {
    compare_cases();
    return 0;
}

// Realiza la comparación entre las directicas 'private' y 'firstPrivate'
void compare_cases() {
    int a=1, b=2, c=3, t=4;
    omp_set_num_threads(3);

    // Inicio de zona paralela donde 'a' no está inicilizada
    // y 'b' debe estart inicializada 
    #pragma omp parallel private(a), firstprivate(b)
    {
        // a Es privada, pero no ha sido inicializada
        // b Es privada, pero ya fue inicializada
        // c Es compartida
        // t Será local ó privada, debido a que cambiamos su valor.
        int t = 5;

        static int s = 8; // Las variables 'static' son públicas
        if (omp_get_thread_num() == 0)
            s = 2;

        printf("thread id: %d, a: %d, b: %d, c: %d, t: %d, s: %d, G: %f, \n", omp_get_thread_num(), a, b, c, t, s, G);
        a = 21;
        b = 22;
        c = 23;
        t = 24;
    }

    printf("\nout of the parallel region\n");
    printf("thread id: %d, a: %d, b: %d, c: %d, t: %d, G: %f, \n", omp_get_thread_num(), a, b, c, t, G);

//    OUTPUT:
//    thread id: 0, a: 0, b: 2, c: 3, t: 5, s: 2, G: 2.100000,
//    thread id: 2, a: 32752, b: 2, c: 3, t: 5, s: 2, G: 2.100000,
//    thread id: 1, a: 32767, b: 2, c: 3, t: 5, s: 2, G: 2.100000,
//
//    out of the parallel region
//    thread id: 0, a: 1, b: 2, c: 23, t: 4, G: 2.100000,
}