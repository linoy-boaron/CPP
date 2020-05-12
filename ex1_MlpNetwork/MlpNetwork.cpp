#include "Matrix.h"
//
// Created by Linoy on 16/12/2019.
//

#include "MlpNetwork.h"
#include "Dense.h"
#include "Digit.h"

/**
     *  implemention :constractor of the MlpNetwork
     * @param weights matrix
     * @param biases matrix
     */

MlpNetwork::MlpNetwork(Matrix *weights, Matrix *biases) :
        _layer0(Dense(weights[0], biases[0], Relu)), _layer1(Dense(weights[1], biases[1], Relu)),
        _layer2(Dense(weights[2], biases[2], Relu)), _layer3(Dense(weights[3], biases[3], Softmax))
{};

/**
    * implement of the operator of ()
    * @param m matrix
    * @return STRUCT digit
    */


Digit MlpNetwork::operator()(Matrix &m)
{
    Matrix r1 = _layer0(m);
    Matrix r2 = _layer1(r1);
    Matrix r3 = _layer2(r2);
    Matrix r4 = _layer3(r3);
    float f = 0;
    int index = 0;
    for (int i = 0; i < 10; i++)
    {
        if (r4[i] > f)
        {
            f = r4[i];
            index = i;
        }
    }

    Digit a;
    a.probability = f;
    a.value = index / r4.getCols();

    return a;

};
