//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    Relu,
    Softmax
};
/**
    * class of Activation
    */
class Activation

{
public:
    /**
     * declaration constractor
     * @param actType
     */
    Activation(ActivationType actType);

    /**
     * declaration
     * @return ActivationType
     */
    ActivationType getActivationType() const;

/**
 * declaration operator () of the class
 * @param m matrix
 * @return matrix
 */
    Matrix operator()(const Matrix &m) const;


private:
    /**
     * field ActivationType declaration
     */
    ActivationType _myact;


    /**
     * declaration
     * @param m
     * @return metrix with action softmax on it from the given matrix
     */
    Matrix _getSoftmax(const Matrix &m) const;

    /**
     * declaration
     * @param m
     * @return matrix ith action relu on it from the given matrix
     */
    Matrix _getRelu(const Matrix &m) const;


};

#endif //ACTIVATION_H
