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
    printf("Loop starting...\n");

    #pragma omp parallel for
    for (int i = 0; i < 10; ++i) {
        printf("%d",i);
    }
    printf("\nLoop ending...\n");
    return 0;
}