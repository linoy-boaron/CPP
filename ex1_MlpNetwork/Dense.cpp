//
// Created by Linoy on 16/12/2019.
//
#include "Dense.h"
#include "Matrix.h"
#include "Activation.h"

/**
 * implement constractor
 * @param w
 * @param bias
 * @param act
 */
Dense::Dense(Matrix &w, Matrix &bias, ActivationType act) : _weights(w), _bias(bias), _act(act)
{};

/**
 * getting weights of the object
 * @return weights
 */

Matrix Dense::getWeights() const
{
    return _weights;
};

/**
 * etting bias of the object
 * @return bias
 */
Matrix Dense::getBias() const
{
    return _bias;
};

/**
 *
 * @return ActivationType of the object
 */
ActivationType Dense::getActivation() const
{
    return _act.getActivationType();
};

/**
 * implement action () of the class
 * @param m matrix
 * @return matrix
 */
Matrix Dense::operator()(Matrix &m)
{
    Matrix output = (_weights * m) + _bias;
    return _act(output);
};
