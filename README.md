# matrix-mult-alg

Este repositorio contiene una serie de algoritmos que implementan la librería `<omp.h>` en el lenguaje C en el marco de la clase de Fundamentos de Programación Paralela de la Universidad Sergio Arboleda. Los algoritmos realizan una multiplicación de matrices: filas por columnas, filas por filas y 2 filas por 2 filas. También se encuentran un archivo orquestador `launcher.pl`, bibliotecas usadas en los scripts (`utilsMM.c` y `utilsMM.h`) y un archivo `makefile` que compila automáticamente los scripts.

---
## Algoritmos
| Archivo      | Descripción |
| ----------- | ----------- |
| algorithm_1      |   Algoritmo de multiplicación de matrices por el método de filas por columnas    |
| algorithm_2  | Algoritmo de multplicación de matrices por el método de filas por filas        |
| algorithm_3  |  Algoritmo de multiplicación de matrices por el método de 2 filas por 2 filas      |
Existe una explicación más detallada [aquí](docs/README.md).

---
## Otros
| Archivo      | Descripción |
| ----------- | ----------- |
| launcher     |   Archivo principal de ejecución de un benchmark entre los tres algoritmos    |
| makefile | Archivo compilador de los scripts de los algoritmos en C       |
| utilsMM  |  Interfaz y módulo que implementa métodos usandos en los scripts de algoritmos     |
---
## Ejecución
Para poder ejecutar el benchmark entre los 3 algoritmos se debe:

1. Clonar el repositorio
2. Parametrizar el archivo `launcher.pl` según el número de repeticiones, hilos y cargas deseadas/disponibles para la multiplicación de matrices.
```perl
@cargas = (144, 288, 576, 720, 960, 1440, 1920);
@threads = (2, 4, 6, 8, 12);
$rep = 20;
```
3. Ejecutar el archivo `laucher.pl` con (el archivo debe tener permisos de ejecución):
```bash
./launcher.pl
```
---
## Resultados
Los resultados son creados en carpetas con el sufijo `.results` en la carpeta raíz donde se ejecuta `launcher.pl`. Cada uno de estas carpetas contendrán archivos de texto con el nombre de la carga y dentro, los resultados separados por hilos.

## Contribuidores
[@sebmancipe](https://github.com/sebmancipe) - _Universidad Sergio Arboleda, Bog. COL_ - <sebastian.mancipe@correo.usa.edu.co>

[@anderballes98](https://github.com/AnderBalles98) - _Universidad Sergio Arboleda, Bog. COL_ - <anderson.ballesteros@correo.usa.edu.co>

## Disclaimer
El código en C de cada uno de los ejercicios fue desarrollado en clase. El uso de los mismos está restringido.
