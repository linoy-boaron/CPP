// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H
//#include <ntdef.h>
#include <fstream>
#include <iostream>

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
    int rows, cols;
} MatrixDims;

// Insert Matrix class here...
/**
    * class of Matrix
    */
class Matrix

{
public:
    /**
     * declaretion constractor Matrix
     * @param rows
     * @param cols
     */
    Matrix(int rows, int cols);
    /**
     * defult declaration of constractor
     */

    Matrix();
    /**
     * declaration of copy constractor
     * @param m
     */

    Matrix(const Matrix &m);
    /**
     * de-constractor declaration
     */

    ~Matrix();
    /**
     * declaration
     * @return num of rows object
     */

    int getRows() const;
    /**
     * declaration
     * @return  num of cols object
     */

    int getCols() const;
    /**
     * declaration
     * @return the matrix in one column
     */

    Matrix &vectorize();
    /**
     * declaration print the matrix
     */

    void plainPrint() const;
    /**
     * assigment declaration
     * @param other
     * @return
     */

    Matrix &operator=(const Matrix &other);
    /**
     * declaration multiply  with matrix
     * @param other matrix
     * @return new matrix that res of the action of multiply
     */

    Matrix operator*(const Matrix &other) const;
    /**
     *declaration multiply with float when its in the right side
     * @param c
     * @return new matrix that res of the action of multiply
     */

    Matrix operator*(const float &c) const;
    /**
     *declaration  friend func - multiply with float when its in the *left* side
     * @param c
     * @return new matrix that res of the action of multiply
     */

    friend Matrix operator*(const float &c, const Matrix &a);
    /**
     * declaration + operator
     * @param other matrix
     * @return new matrix that res of the action of plus
     */

    Matrix operator+(const Matrix &other) const;

/**
     * declaration += operator
     * @param other matrix
     * @return new matrix that res of the action of +=
     */
    Matrix &operator+=(const Matrix &other);
    /**
     * declaration () operator (NOT const version)
     * @param int row, int col
     * @return float in the [row][col] in the metrix
     */
    float &operator()(const int &row, const int &col);
    /**
    * declaration () operator (const version)
    * @param int row, int col
    * @return float in the [row][col] in the metrix
    */

    float operator()(const int &row, const int &col) const;
    /**
    * declaration [] operator ( NOT const version)
    * @param int i
    * @return float in the [i] in the metrix
    */

    float &operator[](const int &i);
    /**
   * declaration [] operator ( const version)
   * @param int i
   * @return float in the [i] in the metrix
   */

    float operator[](const int &i) const;
    /**
     * declaration operator >>
     * @param input stream ,
     * @param matrix D
     * @return input stream loaded in D matrix  .
     */

    friend std::istream &operator>>(std::istream &input, Matrix &D);
    /**
     * declaration operator <<
     * @param os output stream
     * @param D matrix
     * @return output stream with D matrix in pattern of ** (up to the valus)
     */

    friend std::ostream &operator<<(std::ostream &os, const Matrix &D);


private:
    /**
     * declaration field num rows
     */
    int _rows;
    /**
     *  declaration field num cols
     */
    int _cols;
    /**
     * declaration field valus of the matrix
     */
    float *_vals;

};

#endif //MATRIX_H
