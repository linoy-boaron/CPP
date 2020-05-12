//
// Created by Linoy on 16/12/2019.
//

#ifndef CPP_EX1_DENSE_H
#define CPP_EX1_DENSE_H


#include "Matrix.h"
#include "Activation.h"
/**
     * class of Dense
     */
class Dense

{
public:
    /**
     * declaretion constractor
     * @param w
     * @param bias
     * @param act
     */
    Dense(Matrix &w, Matrix &bias, ActivationType act);

/**
 * declaretion
 * @return weights
 */
    Matrix getWeights() const;

    /**
     * declaretion
     * @return bias
     */

    Matrix getBias() const;

    /**
     * declaretion
     * @return ActivationType
     */

    ActivationType getActivation() const;

/**
 * declaretion
 * @param m
 * @return action () of the class
 */
    Matrix operator()(Matrix &m);

/**
 * defult desractor declaretion
 */
    ~Dense() = default;

private:
    /**
     * decleratuon fields
     */
    Matrix _weights;
    Matrix _bias;
    const Activation _act;

};


#endif //CPP_EX1_DENSE_H
