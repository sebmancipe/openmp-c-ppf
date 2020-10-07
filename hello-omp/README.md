# hello-omp

## Descripción
Este ejemplo hace uso de la directiva `parallel` para definir una sección paralela.

```c
#pragma omp parallel
{
    ...
}
```
De esta forma, el número definido de hilos realizará las operaciones dentro de la sección paralela simultáneamente (no necesariamente debe existir un ciclo `for`).
###### Obtenido desde: https://www.openmp.org/wp-content/uploads/OpenMP-API-Specification-5.0.pdf
---
## Output
```bash
hello  2
hello again 2
hello  1
hello again 1
hello  4
hello again 4
hello  3
hello again 3
hello  6
hello again 6
hello  7
hello again 7
hello  0
hello again 0
hello  5
hello again 5
```