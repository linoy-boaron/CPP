//
// Created by Linoy on 15/12/2019.
//
#include "Matrix.h"
#include <iostream>

/**
   *  constractor Matrix
   * @param rows
   * @param cols
   */
Matrix::Matrix(int rows, int cols) : _rows(rows), _cols(cols)
{
    if (rows <= 0 || cols <= 0)
    {
        std::cerr
                << "Error: invalid matrix size for constructor. Please enter a valid rows or columns size."
                << std::endl;
        exit(1);
    }
    _vals = new float[rows * cols];
    for (int i = 0; i < rows * cols; i++)
    {
        _vals[i] = 0.0;
    }
}

/**
 * defult constractor
 */
Matrix::Matrix() : _rows(1), _cols(1)
{
    _vals = new float[_rows * _cols];
    _vals[0] = 0.0;
}
/**
 * copy constractor
 * @param m matrix
 */

Matrix::Matrix(const Matrix &m) : _rows(m._rows), _cols(m._cols)
{
    _vals = new float[_rows * _cols];
    for (int r = 0; r < this->_rows; r++)
    {
        for (int c = 0; c < this->_cols; c++)
        {
            _vals[(_cols * r) + c] = m._vals[(_cols * r) + c];
        }
    }
};
/**
 * de-constractor . free mamory of the object .
 */

Matrix::~Matrix()
{

    delete[] _vals;
    _vals = nullptr;
}
/**
 *
 * @return num of rows
 */

int Matrix::getRows() const
{
    return this->_rows;
}
/**
 *
 * @return num of cols
 */

int Matrix::getCols() const
{
    return this->_cols;
}
/**
 *
 * @return the matrix in one column
 */


Matrix &Matrix::vectorize()
{
    int oldCols = this->_cols;
    this->_cols = 1;
    this->_rows *= oldCols;
    return *this;
}
/**
 * print the matrix
 */

void Matrix::plainPrint() const
{
    for (int r = 0; r < this->_rows; r++)
    {
        for (int c = 0; c < this->_cols; c++)
        {
            std::cout << _vals[(_cols * r) + c] << " ";
        }
        std::cout << std::endl;
    }
}
/**
 *operator assigment implemention
 * @param other matrix
 * @return refrence to the matrix
 */

Matrix &Matrix::operator=(const Matrix &other)
{
    if (this == &other)
    { return *this; }
    this->_cols = other._cols;
    this->_rows = other._rows;
    delete[] this->_vals;
    this->_vals = new float[other._cols * other._rows];
    for (int r = 0; r < this->_rows; r++)
    {
        for (int c = 0; c < this->_cols; c++)
        {
            this->_vals[(_cols * r) + c] = other._vals[(_cols * r) + c];
        }
    }
    return *this;
};
/**
     * implement  multiply  with matrix
     * @param other matrix
     * @return new matrix that res of the action of multiply
     */
Matrix Matrix::operator*(const Matrix &other) const
{
    if (this->_cols != other._rows)
    {
        std::cerr << "Error: invalid matrix size for multiplication using * operator." << std::endl;
        exit(1);
    }
    Matrix myM = Matrix(this->_rows, other._cols);
    int i, j, k;
    for (i = 0; i < _rows; i++)
    {
        for (j = 0; j < other._cols; j++)
        {
            for (k = 0; k < _cols; k++)
            {
                myM._vals[(i * myM._cols) + j] +=
                        this->_vals[(i * this->_cols) + k] * other._vals[(k * other._cols) + j];
            }
        }
    }

    return myM;
}

/**
     *implement multiply with float when its in the right side
     * @param c float
     * @return new matrix that res of the action of multiply
     */

Matrix Matrix::operator*(const float &c) const
{
    Matrix myM = Matrix(_rows, _cols);
    for (int r = 0; r < _rows; r++)
    {
        for (int co = 0; co < _cols; co++)
        {
            myM._vals[(_cols * r) + co] =
                    (this->_vals[(_cols * r) + co]) * c;

        }
    }

    return myM;

}
/**
   * implement + operator
   * @param other matrix
   * @return new matrix that res of the action of plus
   */

Matrix Matrix::operator+(const Matrix &other) const
{
    if (other._rows != this->_rows || other._cols != this->_cols)
    {
        std::cerr << "Error: invalid matrix size for adding using + operator." << std::endl;
        exit(1);
    }
    Matrix myM = Matrix(_rows, _cols);
    for (int r = 0; r < other._rows; r++)
    {
        for (int co = 0; co < other._cols; co++)
        {
            myM._vals[(myM._cols * r) + co] =
                    this->_vals[(this->_cols * r) + co] + other._vals[(other._cols * r) + co];
        }
    }
    return myM;
}

/**
     * implement += operator
     * @param other matrix
     * @return new matrix that res of the action of +=
     */

Matrix &Matrix::operator+=(const Matrix &other)
{
    if (other._rows != this->_rows || other._cols != this->_cols)
    {
        std::cerr << "Error: invalid matrix size for adding using + operator." << std::endl;
        exit(1);
    }
    for (int r = 0; r < _rows; ++r)
    {
        for (int co = 0; co < _cols; ++co)
        {
            this->_vals[(_cols * r) + co] =
                    this->_vals[(_cols * r) + co] + other._vals[(_cols * r) + co];

        }
    }
    return *this;

}
/**
   * implement () operator (const version)
   * @param int row, int col
   * @return float in the [row][col] in the metrix
   */


float Matrix::operator()(const int &row, const int &col) const
{
    if (col < 0 || col >= getCols() || row < 0 || row >= getRows())
    {
        std::cerr << "Error: invalid array index. Input should be lower then cols*rows"
                  << std::endl;
        exit(1);
    }
    return _vals[(_cols * row) + col];
}
/**
   * implement [] operator (  const version)
   * @param int i
   * @return float in the [i] in the metrix
   */


float Matrix::operator[](const int &i) const
{
    if (i >= _cols * _rows || i < 0)
    {
        std::cerr << "Error: invalid array index. Input should be lower then cols*rows"
                  << std::endl;
        exit(1);
    }
    return _vals[i];
}

/**
     * implement () operator (NOT const version)
     * @param int row, int col
     * @return float in the [row][col] in the metrix
     */

float &Matrix::operator()(const int &row, const int &col)
{
    if (col < 0 || col >= getCols() || row < 0 || row >= getRows())
    {
        std::cerr << "Error: invalid array index. Input should be lower then cols*rows"
                  << std::endl;
        exit(1);
    }
    return _vals[(_cols * row) + col];
}

/**
   * implement [] operator (   NOT const version)
   * @param int i
   * @return float in the [i] in the metrix
   */

float &Matrix::operator[](const int &i)
{
    if (i >= _cols * _rows || i < 0)
    {
        std::cerr << "Error: invalid array index. Input should be lower then cols*rows"
                  << std::endl;
        exit(1);
    }
    return _vals[i];
}
/**
     *implement  friend func - multiply with float when its in the *left* side
     * @param c float
     * @return new matrix that res of the action of multiply
     */


Matrix operator*(const float &c, const Matrix &a)
{
    Matrix myM(Matrix(a._rows, a._cols));
    for (int r = 0; r < a._rows; ++r)
    {
        for (int co = 0; co < a._cols; ++co)
        {
            myM._vals[(a._cols * r) + co] =
                    c * (a._vals[(a._cols * r) + co]);
        }
    }
    return myM;
}

/**
     * implement operator >>
     * @param input stream ,
     * @param matrix D
     * @return input stream loaded in D matrix  .
     */

std::istream &operator>>(std::istream &input, Matrix &D)
{
    float num = 0;
    for (int i = 0; i < D._rows * D._cols; i++)
    {
        input.read((char *) (&num), sizeof(float));
        D._vals[i] = num;
        if (!input.good())
        {
            std::cout << "Error reading the Matrix input" << std::endl;
            exit(1);
        }
    }

    return input;
}
/**
     * implement operator <<
     * @param os output stream
     * @param D matrix
     * @return output stream with D matrix in pattern of ** (up to the  matrix valus)
     */

std::ostream &operator<<(std::ostream &os, const Matrix &D)
{
    if (!os.good())
    {
        std::cout << "Error printing the Matrix output" << std::endl;
        exit(1);
    }

    for (int i = 0; i < D._rows; i++)
    {
        for (int j = 0; j < D._cols; j++)
        {
            if (D._vals[i * D._cols + j] <= 0.1f)
            {
                os << "  ";
            }
            else
            {
                os << "**";
            }
        }
        os << "\n";
    }
    return os;
}




