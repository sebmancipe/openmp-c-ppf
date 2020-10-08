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
    // Inicio zona paralela
    // Cada hilo realizará las mimas acciones que se encuentren
    // dentro de la zona paralela
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf("hello  %d\n", ID);
        printf("hello again %d\n", ID);
    }
    return 0;
}