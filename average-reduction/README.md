# average-reduction
## Descripción
Este ejercicio demuestra el uso de la directiva de OpenMP `reduction` junto con una comparación con un algoritmo que tiene la misma finalidad, pero realizar su operación con la cláusula `atomic`.
Esta directiva indica una variable y operación que se realizará sobre la misma. Todos los hilos tendrán esta variable como privada pero al finalizar la sección paralela, se realizará la operación especificada, uniendo los resultados individuales de los hilos. 
###### Obtenido desde: https://www.openmp.org/wp-content/uploads/OpenMP-API-Specification-5.0.pdf
---
## Output
