# parallel-loop

## Descripción
El ejercicio desarrolla un ejemplo básico de paralelismo con la directiva `for`:
```c
#pragma omp parallel for
{
    for (int i = 0; i < 10; ++i) {
        printf("%d",i);
    }
}

```
Esta sección paralela indica a cada hilo que ejecute parte de la iteración y la imprima.

###### Obtenido desde: https://www.openmp.org/wp-content/uploads/OpenMP-API-Specification-5.0.pdf
---
## Output
```bash
Loop starting...
5601842379
Loop ending...
```