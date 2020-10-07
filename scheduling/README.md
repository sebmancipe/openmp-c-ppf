# scheduling

## Descripción
Este algoritmo ejecuta varios ciclos `for` con variantes de la directiva `schedule()`, que controla cómo las iteraciones se dividen entre los hilos. El tipo de esta directiva puede ser:
### static
```c
#pragma omp parallel for num_threads(2) schedule(static)
{
    ...
}
```
Indica que a cada hilo se le entregará un número _n_ de iteraciones progresivamente. Esta asignación es hecha **durante la compilación**.

### dynamic
```c
#pragma omp parallel for num_threads(2) schedule(dynamic)
{
    ...
}
```
Indica que a cada hilo se le entregará un número _n_ de iteraciones pero no será balanceado (si un hilo se desocupa, tomará nuevamente otra carga). Esta asignación es hecha **durante la ejecución**.

En ambos casos, puede definirse un tamaño de `chunk`: `schedule(dynamic, chunk)` que será el número de iteraciones que realizará cada hilo por ejecución.

###### Obtenido desde: https://www.openmp.org/wp-content/uploads/OpenMP-API-Specification-5.0.pdf

---
## Output
```bash
Thread 0 is doing iteration 0.
Thread 0 is doing iteration 1.
Thread 0 is doing iteration 2.
Thread 0 is doing iteration 3.
Thread 0 is doing iteration 4.
Thread 1 is doing iteration 5.
Thread 1 is doing iteration 6.
Thread 1 is doing iteration 7.
Thread 1 is doing iteration 8.
Thread 1 is doing iteration 9.
Thread 0 is doing iteration 0.
Thread 0 is doing iteration 1.
Thread 0 is doing iteration 2.
Thread 0 is doing iteration 3.
Thread 0 is doing iteration 8.
Thread 0 is doing iteration 9.
Thread 1 is doing iteration 0.
Thread 1 is doing iteration 1.
Thread 1 is doing iteration 2.
```