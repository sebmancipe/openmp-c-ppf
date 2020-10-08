/*
* Author of C++ script: Mustafa Atik - muatik@gmail.com 
* Authors of C script: 
*   Anderson Ballesteros - anderson.ballesteros@correo.usa.edu.co 
*   Sebastian Mancipe - sebastian.mancipe@correo.usa.edu.co
* Sergio Arboleda University
* Bogota, Colombia
* 2020
*/

#include <stdlib.h>
#include <stdio.h>

// Creación de la estructura
struct Matrix
{
    // atributos, valores ó datos que hacen parte de esta estructura
    double *data;
    int rows, cols;
};

// Inicializa la estructura recibida por parmámetro
void init(struct Matrix *const matrixInstance, int rows, int cols)
{
    matrixInstance->rows = rows;
    matrixInstance->cols = cols;
    matrixInstance->data = (double *) malloc(rows * cols);
}

// Retorna el atributo 'data' de la estructura recibida por parámetro
double get(struct Matrix *const matrixInstance, int row, int col)
{
    return matrixInstance->data[row * matrixInstance->cols + col];
}

// Modifica y retorna la nueva 'data' de la estructura recibida por parámetro
double set(struct Matrix *const matrixInstance, int row, int col, double val)
{
    matrixInstance->data[row * matrixInstance->cols + col] = val;
}


struct Matrix operator(const Matrix &m2)
{
    return sum(m2);
}

// Se crea el método 'sum' internos para cada matriz con el fin de sumar esta misma con otra recibida por parámetro
// Retorna el resultado de la suma 
Matrix &sum(Matrix matrix)
{
    Matrix *s = new Matrix(rows, cols);
    for (int i = 0; i < rows * cols; ++i)
    {
        s->data[i] = data[i] + matrix.data[i];
    }
    return *s;
}

// Se crea el método 'substrac' internos para cada matriz con el fin de restar esta misma con otra recibida por parámetro
// Retorna el resultado de la resta 
Matrix &substract(Matrix matrix)
{
    Matrix *s = new Matrix(rows, cols);
    for (int i = 0; i < rows * cols; ++i)
    {
        s->data[i] = data[i] - matrix.data[i];
    }
    return *s;
}

// Se crea el método 'multiply' privado para cada matriz con el fin de multiplicar esta mismo con otra recibida por parámetro
// Retorna el resultado de la multiplicación 
Matrix &multiply(Matrix matrix)
{
    if (!(shape()[0] == matrix.shape()[1] && shape()[1] == matrix.shape()[0]))
        throw std::invalid_argument("shape does not fit each other");

    Matrix *s = new Matrix(rows, cols);
    for (int i = 0; i < rows * cols; ++i)
    {
        s->data[i] = data[i] - matrix.data[i];
    }
    return *s;
}

// Se crea el método 'T' privado para cada matriz con el fin de hallar la transpuesta de la misma
// Retorna la matriz transpuesta
Matrix &T()
{
    Matrix *s = new Matrix(cols, rows);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            s->set(j, i, get(i, j));
        }
    }
    return *s;
}

// Retorna un aputador que almacena la cantidad de fila y columnas
int *shape()
{
    int *shape = new int[2];
    shape[0] = rows;
    shape[1] = cols;
    return shape;
}

int main()
{
    Matrix m1 = Matrix(2, 3);
    Matrix m2 = Matrix(2, 3);
    for (int i = 0; i < 6; ++i)
    {
        m1.set((int)i / 3, i % 3, i);
        m2.set((int)i / 3, i % 3, i);
    }

    m1.set(0, 1, 6);

    return 0;
}