# openmp-c-ppf

Este repositorio contiene una serie de ejercicios que implementan la librería `<omp.h>` en el lenguaje C. Estos ejercicios fueron obtenidos del repositorio del usuario [@muatick](https://github.com/muatik) [_openmp-examples_](https://github.com/muatik/openmp-examples) e interpretados para construir las implementaciones en C (originalmente se encuentran en C++). Los ejercicios están basados, según el autor en:
> _Introduction to OpenMP:_ A Youtube playlist explaining OpenMP use. Can be checked [here](https://www.youtube.com/watch?v=nE-xN4Bf8XI&list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG).
>
> _Other related bibliography:_ 
>* Guide into OpenMP Easy multithreading programming for C++. Is avaliable [here](https://bisqwit.iki.fi/story/howto/openmp/).
>* 32 OpenMP Traps For C++ Developers. Can be found [here](https://www.viva64.com/en/a/0054/).

---
## Ejercicios
| Carpeta      | Descripción |
| ----------- | ----------- |
| scheduling      |   Tipos de distribución de cargas     |
| parallel-loop  | Implementación simple de un ciclo for paralelizado        |
| matrix  |         |
| linked-list  |  Paralelización del procesamiento de una estructura de datos      |
| integral  |  Diferentes enfoques para obtener el valor de PI      |
| hello-omp  | Implementación de una región paralela    |
| head-vs-stack  |  Diferencias entre la definción de variables dentro y fuera de la sección paralela   |
| data-sharing  | Variables compartidas y privadas inicializadas y no inicializadas     |
| average-reduction  | Uso de la cláusula reduction y comparación con un algoritmo que no la implementa   |
| als-movie-recommender  |     |
---
## Ejecución
Para poder ejecutar los scripts deben compilarse y ejecutarse con `gcc` junto con la bandera `-fopenmp` dentro de la carpeta del ejercicio. 
```bash
gcc -fopenmp main.c -o main
./main
```
