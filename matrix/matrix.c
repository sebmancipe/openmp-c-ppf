#include <stdlib.h>
#include <stdio.h>

struct Matrix
{
    double *data;
    int rows, cols;
};

void init(struct Matrix *const matrixInstance, int rows, int cols)
{
    matrixInstance->rows = rows;
    matrixInstance->cols = cols;
    matrixInstance->data = (double *) malloc(rows * cols);
}

double get(struct Matrix *const matrixInstance, int row, int col)
{
    return matrixInstance->data[row * matrixInstance->cols + col];
}

double set(struct Matrix *const matrixInstance, int row, int col, double val)
{
    matrixInstance->data[row * matrixInstance->cols + col] = val;
}

struct Matrix operator+(const Matrix &m2)
{
    return sum(m2);
}

Matrix &sum(Matrix matrix)
{
    Matrix *s = new Matrix(rows, cols);
    for (int i = 0; i < rows * cols; ++i)
    {
        s->data[i] = data[i] + matrix.data[i];
    }
    return *s;
}

Matrix &substract(Matrix matrix)
{
    Matrix *s = new Matrix(rows, cols);
    for (int i = 0; i < rows * cols; ++i)
    {
        s->data[i] = data[i] - matrix.data[i];
    }
    return *s;
}

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

int *shape()
{
    int *shape = new int[2];
    shape[0] = rows;
    shape[1] = cols;
    return shape;
}

__STRING toString()
{
    std::stringstream ss;
    ss << "[" << std::endl
       << " [";
    for (int i = 0; i < rows * cols; ++i)
    {
        if (i != 0 && i % cols == 0)
            ss << "]" << std::endl
               << " [";
        ss << " " << data[i] << " ";
    }
    ss << "]" << std::endl
       << "]";
    return ss.str();
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
    printf('%s', m1.toString());
    printf('%s', m2.toString());
    printf('%s', (m1 + m2).toString());
    printf('%s', m2.T().T().T().toString());

    return 0;
}