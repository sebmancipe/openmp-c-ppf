/*
# * Archivo: utilsMM.c
# * Autor: Sebastian Mancipe <sebastian.mancipe@correo.usa.edu.co>
# * Última Modificación: 14 de Octubre, 2020
# * ----------------------------------------------------------------
# * El archivo utilsMM.c contiene la implementación de las funciones declaradas
# * por la interfaz utilsMM.h que son usadas en el archivo algorithm_*.c. Principalmente
# * se encuentran inicialización de argumentos, tomas de tiempos y presentación
# * de resultados.
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#include <errno.h>
#include "utilsMM.h"

#define MAX_THREADS 16

struct timeval start[MAX_THREADS];
struct timeval stop[MAX_THREADS];
static int nThreads;

void mmStart(int threadId)
{ // Inicio de toma de tiempo
#pragma omp barrier
    gettimeofday(start + threadId, NULL);
}

void mmStop(int threadId)
{ // Fin de toma de tiempo
    gettimeofday(stop + threadId, NULL);
}

// Inicialización de argumentos
void argsInit(int argc, char *argv[])
{
    nThreads = (int)atof(argv[1]);

    if (!nThreads || nThreads > MAX_THREADS)
    {
        printf("Número de threads no válido");
        exit(1);
    }

    omp_set_num_threads(nThreads);
}

// Inicializar datos
int mmParallel(void)
{
    int thread;
    thread = omp_get_thread_num();
    return thread;
}

// Presentar datos
void mmEnd(void)
{
    double prom = 0.0, currentTime = 0.0;
    for (int thread = 0; thread < nThreads; thread++)
    {
        stop[thread].tv_usec -= start[thread].tv_usec;
        if (stop[thread].tv_usec < 0)
        {
            stop[thread].tv_usec += 1000000;
            stop[thread].tv_sec--;
        }

        stop[thread].tv_sec -= start[thread].tv_sec;

        currentTime = stop[thread].tv_sec + stop[thread].tv_usec / 1000000.0;
        //printf("Thread %d %.3f\n", thread, currentTime);
        prom += currentTime;
    }
    printf("%.3f\n", prom / nThreads);
}
