#include "Header.h"

Matrix::~Matrix()
{
    for (int i = 0; i < size; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

Matrix::Matrix(int size)
{
    this->matrix = new double* [size];
    for (int i = 0; i < size; i++)
    {
        this->matrix[i] = new double[size];
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                this->matrix[i][j] = 1;
            }
            else
            {
                this->matrix[i][j] = 0;
            }
        }
    }
    this->size = size;
    this->name = "E";
}

Matrix::Matrix(string name, int size, double** matrix)
{
    this->name = name;
    this->size = size;
    this->matrix = matrix;
}

Matrix::Matrix(const Matrix& matrix)
{
    this->size = matrix.size;
    this->matrix = new double* [size];
    for (int i = 0; i < size; ++i)
    {
        this->matrix[i] = new double[size];
        for (int j = 0; j < size; ++j)
        {
            this->matrix[i][j] = matrix.matrix[i][j];
        }
    }
    this->name = matrix.name;
}

Matrix::Matrix(Matrix&& matrix)
{
    name = matrix.name;
    size = matrix.size;
    this->matrix = matrix.matrix;
    matrix.matrix = NULL;
    matrix.size = 0;
}

Matrix::Matrix(string name, int size, double num = 0.)
{
    this->size = size;
    this->name = name;
    matrix = new double* [size];
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new double[size];
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = num;
        }
    }
}

Matrix::Matrix(string name, int size, int num)
{
    this->name = name;
    this->size = size;
    matrix = new double* [size];
    for (int i = 0; i < size; i++)
    {
        matrix[i] = new double[size];
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = rand() % num;
        }
    }
}

Matrix& Matrix::operator=(Matrix&& right)
{
    if (this == &right)
        return *this;
    matrix = right.matrix;
    name = right.name;
    size = right.size;
    right.matrix = nullptr;
    right.size = 0;
    return *this;
}

Matrix& Matrix::operator=(const Matrix& right)
{
    if (&right == this)
        return *this;
    delete[] this->matrix;
    this->size = right.size;
    this->matrix = new double* [size];
    for (int i = 0; i < size; i++)
    {
        this->matrix[i] = new double[size];
        for (int j = 0; j < size; j++)
        {
            this->matrix[i][j] = right.matrix[i][j];
        }
    }
    this->name = right.name;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& right)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            this->matrix[i][j] += right.matrix[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& right)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            this->matrix[i][j] -= right.matrix[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator/=(const int n)
{
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->size; ++j)
        {
            this->matrix[i][j] /= n;
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& right)
{

    double** tmp = new double* [size];
    for (int i = 0; i < size; i++)
    {
        tmp[i] = new double[size];
        for (int j = 0; j < size; j++)
        {
            tmp[i][j] = 0;
        }
    }
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < size; ++k)
            {
                tmp[i][j] += this->matrix[i][k] * right.matrix[k][j];
            }
        }
    }
    for (int m = 0; m < size; ++m) {
        for (int i = 0; i < size; ++i) {
            this->matrix[m][i] = tmp[m][i];
        }
    }

    for (int i = 0; i < size; i++)
    {
        delete[] tmp[i];
    }
    delete[] tmp;
    return *this;
}

Matrix Matrix::operator/(const int n)
{
    Matrix result(*this);
    return result /= n;
}

Matrix Matrix::operator*(const Matrix& right)
{
    Matrix result(*this);
    return result *= right;
}

Matrix Matrix::operator+(const Matrix& right)
{
    Matrix result(*this);
    return result += right;
}

Matrix Matrix::operator-(const Matrix& right)
{
    Matrix result(*this);
    return result -= right;
}

bool Matrix::operator==(const Matrix& right)
{
    if (this->size != right.size)
        return false;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (this->matrix[i][j] != right.matrix[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& right)
{
    return !(*this == right);
}

const Matrix Matrix::reduceColRow(int row, int col) const
{
    double** temp_matr = new double* [size - 1];
    for (int i = 0; i < size - 1; ++i)
    {
        temp_matr[i] = new double[size - 1];
    }

    int ki = 0;
    for (int i = 0; i < size; i++)
    {
        if (i != row) {
            for (int j = 0, kj = 0; j < size; j++)
            {
                if (j != col)
                {
                    temp_matr[ki][kj] = matrix[i][j];
                    kj++;
                }
            }
            ki++;
        }
    }
    Matrix result(name, size - 1, temp_matr);

    return result;
}

void Matrix::print()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

double getTrace(const Matrix& matrix)
{
    double result = 0;
    for (int i = 0; i < matrix.size; i++)
    {
        result += matrix.matrix[i][i];
    }
    return result;
}

double getDeterminant(const Matrix matrix)
{
    if (matrix.size == 1)
        return matrix.matrix[0][0];
    double det = 0;
    double sg = -1;
    for (int i = 0; i < matrix.size; i++)
    {
        sg *= -1;
        Matrix add = matrix.reduceColRow(i, 0);
        det += matrix.matrix[i][0] * sg * (getDeterminant(add));
    }
    return det;
}

Matrix reverse(const Matrix& matrix)
{
    int sgn;
    double det = getDeterminant(matrix);
    Matrix adj(matrix.name, matrix.size);
    for (int i = 0; i < matrix.size; ++i)
    {
        for (int j = 0; j < matrix.size; ++j)
        {

            sgn = (((i + j) % 2 == 0) ? 1 : -1);
            adj.matrix[i][j] = (sgn * getDeterminant(matrix.reduceColRow(i, j))) / det;
        }
    }
    adj = transpose(adj);
    return adj;
}

Matrix transpose(const Matrix& matrix)
{
    Matrix result(matrix.name, matrix.size);
    for (int i = 0; i < matrix.size; ++i)
    {
        for (int j = 0; j < matrix.size; ++j)
        {
            result.matrix[i][j] = matrix.matrix[j][i];
        }
    }
    return result;
}

Matrix exp(const Matrix& matrix, int n) {
    int d = 1;
    Matrix result = Matrix(matrix.size);
    Matrix a = matrix;
    for (int i = 0; i < matrix.size; ++i)
    {
        result = result + a / d++;
        a *= matrix;
    }

    return result;

}

ostream& operator<<(ostream& out, const Matrix& matrix)
{
    out << matrix.name << " " << matrix.size << " \n";
    for (int i = 0; i < matrix.size; i++)
    {
        for (int j = 0; j < matrix.size; j++)
        {
            out << matrix.matrix[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

istream& operator>>(istream& in, Matrix& matrix)
{
    in >> matrix.name;
    in >> matrix.size;
    for (int i = 0; i < matrix.size; ++i)
    {
        for (int j = 0; j < matrix.size; ++j)
        {
            in >> matrix.matrix[i][j];
        }
    }
    return in;
}