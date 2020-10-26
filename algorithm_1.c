/*
# * Archivo: algorithm_1.c
# * Autor: Sebastian Mancipe <sebastian.mancipe@correo.usa.edu.co>
# * Última Modificación: 13 de Octubre, 2020
# * ----------------------------------------------------------------
# * El archivo algorithm_1.c es el archivo principal que realiza la multiplicación entre dos matrices
# * usando funciones del módulo utilsMM.c con filas por columnas.
# * Cuando se trae el bloque de memoria aquí, se usa un solo campo.
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

//Only for debug purposes
void printArray(int SZ, double *a)
{
    int j, k;

    for (k = 0; k < SZ; k++)
    {
        for (j = 0; j < SZ; j++)
        {
            printf("%f ", a[j + k * SZ]);
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
        printf("algorithm_1 sizeMatrix nThreads\n");
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
    for (i = 0; i < SZ; i++)
        for (j = 0; j < SZ; j++)
        {
            double *pA, *pB, S;
            S = 0.0;
            pA = a + (i * SZ);
            pB = b + j;
            for (k = SZ; k > 0; k--, pA++, pB += SZ)
            {
                //printf("pA is %f and pB is %f\n", *pA, *pB);
                S += (*pA * *pB);
            }
            c[i * SZ + j] = S;
        }

    // Invocación de función de toma de rendimiento (fin)
    mmStop(threadId);
    //printArray(SZ, c);
    //Invocación de función que presente el tiempo final por cada hilo
    mmEnd();
    return 0;
}
