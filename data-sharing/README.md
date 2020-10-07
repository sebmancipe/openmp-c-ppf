# data-sharing

## Descripción
Este ejercicio demuestra el uso de las directivas `private` y `firstprivate` al momento de ejecutar una sección paralela. La principal diferencia recae en la inicialización o no de la variable puesta en la directiva, donde `firstprivate` inicializa el valor para cada hilo según el valor que ya exista anteriormente de la variable y `private` no. Las variables no definidas dentro de las directivas se asumirán compartidas.
###### Obtenido desde: https://www.openmp.org/wp-content/uploads/OpenMP-API-Specification-5.0.pdf
---
## Output
```c
thread id: 0, a: 0, b: 2, c: 3, t: 5, s: 2, G: 2.100000, 
thread id: 2, a: 0, b: 2, c: 3, t: 5, s: 2, G: 2.100000, 
thread id: 1, a: 0, b: 2, c: 3, t: 5, s: 8, G: 2.100000, 

out of the parallel region
thread id: 0, a: 1, b: 2, c: 23, t: 4, G: 2.100000,
```