# linked-list

## Descripción
El algoritmo realiza un "procesamiento" paralelizado de un número definido de nodos dentro de una cola. La sección paralelizada es definida con la directiva `#pragma omp parallel` junto con una manipulación atómica de la variable `totalProcessedCounter` con `#pragma omp atomic`. La estructura del código es de la siguiente forma:

```c
#pragma omp parallel
{
    ...
    while(remove_node(queue) != NULL)
    {
        proccessNode();
        processedCounter++;
    }
    ...
    #pragma omp atomic
    totalProcessedCounter += processedCounter;
    ...
}
```
La conclusión de este ejercicio es la asignación no balanceada de cargas (procesamiento de nodos) junto con la aserción de la información de manera centralizada.

###### Obtenido desde: https://www.openmp.org/wp-content/uploads/OpenMP-API-Specification-5.0.pdf
---
## Output
```
Thread id: 3,  processed: 24 nodes, took: 0.885159 seconds 
Thread id: 1,  processed: 18 nodes, took: 0.885812 seconds 
Thread id: 0,  processed: 16 nodes, took: 0.904708 seconds 
Thread id: 4,  processed: 22 nodes, took: 0.936555 seconds 
Thread id: 2,  processed: 20 nodes, took: 0.944208 seconds 
End. Processed 100 nodes. Took 0.945323 in total
```