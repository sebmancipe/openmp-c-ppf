# heap-vs-stack

## Descripción
El ejemplo demuestra el comportamiento de una sección paralela definida por la directiva `parallel` cuando se define una variable **dentro** de la sección paralela y **por fuera**.
```c
int heap_sum = 0;
#pragma omp parallel
{
    int stack_sum=0;
    stack_sum++;
    heap_sum++;
    ...
}
```
Para el caso de la variable fuera de la secciòn paralela `heap_sum` su valor será compartido y por lo tanto, acumulativo entre todos los hilos. La variable `stack_sum`, por otro lado, tendrá un valor interno y se sobreescribirá al momento de ejecutarse cada hilo.
###### Obtenido desde: https://www.openmp.org/wp-content/uploads/OpenMP-API-Specification-5.0.pdf
---
## Output
```bash
stack sum is 1
heap sum is 3
stack sum is 1
heap sum is 3
stack sum is 1
heap sum is 3
final heap sum is 3
```
