//
// Created by Linoy on 16/12/2019.
//

#include <iostream>
#include "Activation.h"
#include <cmath>

/**
 * implement constractor
 * @param actType
 */
Activation::Activation(ActivationType actType)
{
    _myact = actType;
}

/**
	* implement get type
	* @return ActivationType
	*/
ActivationType Activation::getActivationType() const
{
    return _myact;
}

/**
 *
 * @param matrix to do with its valus the relu action
 * @return metrix
 */

Matrix Activation::_getRelu(const Matrix &m) const
{
    Matrix tmp(m);
    for (int r = 0; r < m.getRows(); r++)
    {
        for (int c = 0; c < m.getCols(); c++)
        {
            if ((tmp[(m.getCols() * r) + c]) < 0)
            {
                tmp[(m.getCols() * r) + c] = 0;
            }
        }
    }
    return tmp;
}

/**
 * matrix to do with its valus the softmax action
 * @param m
 * @return
 */

Matrix Activation::_getSoftmax(const Matrix &m) const
{
    Matrix myMatrix(m);
    float sum = 0;
    int matrixLen = m.getRows() * m.getCols();
    for (int index = 0; index < matrixLen; index++)
    {
        sum = sum + std::exp(m[index]);
        myMatrix[index] = std::exp(m[index]);
    }

    for (int temp = 0; temp < matrixLen; temp++)
    {
        myMatrix[temp] = (1 / sum) * myMatrix[temp];
    }
    return myMatrix;
}

/**
 * implement operator () of the class
 * @param m matrix
 * @return matrix
 */
Matrix Activation::operator()(const Matrix &m) const
{
    if (_myact == ActivationType::Relu)
    {
        return _getRelu(m);
    }
    else if (_myact == ActivationType::Softmax)
    {
        return _getSoftmax(m);
    }
    else
    {
        std::cerr << "Error: invalid activation type." << std::endl;
        exit(1);
    }
}


