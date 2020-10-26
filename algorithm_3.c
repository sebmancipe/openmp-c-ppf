/*
# * Archivo: algorithm_3.c
# * Autor: Sebastian Mancipe <sebastian.mancipe@correo.usa.edu.co>
# * Última Modificación: 15 de Octubre, 2020
# * ----------------------------------------------------------------
# * El archivo algorithm_3.c es el archivo principal que realiza la multiplicación entre dos matrices
# * usando funciones del módulo utilsMM.c con 2 filas por 2 filas a la vez.
# * Cuando se trae el bloque aquí, se usan los 64 campos.
# * Existen impresiones comentadas que son utilizadas como debug.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include "utilsMM.h"

#define DATA_SZ (1024 * 1024 * 64 * 3)

static double MEM_CHUNK[DATA_SZ];

void matrixInitCol(int SZ, double *a, double *b, double *c)
{
    int j, k, l = 1, m = -1;

    for (k = 0; k < SZ; k++)
        for (j = 0; j < SZ; j++)
        {
            a[j + k * SZ] = l++;
            b[j + k * SZ] = m--;
            c[j + k * SZ] = 1.0;
        }
}

// Only for debug purposes
void printArray(int SZ, double *a)
{
    int j, k;

    for (k = 0; k < SZ; k++)
    {
        for (j = 0; j < SZ; j++)
        {
            printf("%.f ", a[j + k * SZ]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int N;
    //Ingreso de número correcto de argumentos
    if (argc <= 2)
    {
        printf("algorithm_3 sizeMatrix nThreads\n");
        return -1;
    }

    N = (int)atof(argv[1]);
    argc--;
    argv++;

    if (N > 1024 * 8)
    {
        printf("Invalid MatrixSize\n");
        return -1;
    }

    // Función que inicialice los argumentos (tamaño e hilos)
    argsInit(argc, argv);

    // Inicio de sección paralela
#pragma omp parallel
    {
        int i, j, k, threadId, SZ = N;
        double *a, *b, *c;
        a = MEM_CHUNK;
        b = a + SZ * SZ;
        c = b + SZ * SZ;

        // Función de inicialización paralelo
        mmParallel();

        // Identificación de hilos establecidos (threadId)
        threadId = omp_get_thread_num();

        // Debería ser hecho por un solo hilo (master)
#pragma omp master
        matrixInitCol(SZ, a, b, c);

        //printArray(SZ, a);
        //printArray(SZ, b);

        // Invocación de función toma de rendimiento (inicio)
        mmStart(threadId);

        // Inicio de sección paralela "for"
#pragma omp for
        for (i = 0; i < SZ; i += 2)
            for (j = 0; j < SZ; j += 2)
            {
                double *pA, *pB, c0, c1, c2, c3;
                c0 = c1 = c2 = c3 = 0.0;

                pA = a + (i * SZ);
                pB = b + (j * SZ);

                //printf("(i * SZ) is %d\n(j * SZ) is %d\n", (i * SZ), (j * SZ));
                for (k = SZ; k > 0; k -= 2, pA += 2, pB += 2)
                {
                    double a0, a1, a2, a3, b0, b1, b2, b3;
                    // The aN is going to store the positions of a square matrix at the left side of the matrix
                    a0 = *pA;
                    a1 = *(pA + 1);
                    a2 = *(pA + SZ);
                    a3 = *(pA + SZ + 1);

                    // The bN is going to store the positions of a square matrix at the right side of the matrix
                    b0 = *pB;
                    b1 = *(pB + 1);
                    b2 = *(pB + SZ);
                    b3 = *(pB + SZ + 1);

                    /*
                    printf("c0 += (a0= %.f * b0= %.f) + (a1= %.f * b1= %.f)\n", a0, b0, a1, b1);
                    printf("c1 += (a0= %.f * b2= %.f) + (a1= %.f * b3= %.f)\n", a0, b2, a1, b3);
                    printf("c2 += (a2= %.f * b0= %.f) + (a3= %.f * b1= %.f)\n", a2, b0, a3, b1);
                    printf("c3 += (a2= %.f * b2= %.f) + (a3= %.f * b3= %.f)\n\n", a2, b2, a3, b3);*/

                    c0 += a0 * b0 + a1 * b1;
                    c1 += a0 * b2 + a1 * b3;
                    c2 += a2 * b0 + a3 * b1;
                    c3 += a2 * b2 + a3 * b3;
                }

                pB = c + i * SZ + j;
                *pB = c0;
                *(pB + 1) = c1;
                *(pB + SZ) = c2;
                *(pB + SZ + 1) = c3;

                //printArray(SZ, c);
            }

        // Invocación de función de toma de rendimiento (fin)
        mmStop(threadId);
    }

    //Invocación de función que presente el tiempo final por cada hilo
    mmEnd();
    return 0;
}
