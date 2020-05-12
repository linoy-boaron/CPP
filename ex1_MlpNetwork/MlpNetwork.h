//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Dense.h"
#include "Digit.h"

#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784},
                                  {64,  128},
                                  {20,  64},
                                  {10,  20}};
const MatrixDims biasDims[] = {{128, 1},
                               {64,  1},
                               {20,  1},
                               {10,  1}};

// Insert MlpNetwork class here...
/**
* class of MlpNetWork
 */
class MlpNetwork

{
public:
    /**
     *  declaration :constractor of the MlpNetwork
     * @param weights matrix
     * @param biases matrix
     */
    MlpNetwork(Matrix *weights, Matrix *biases);

    /**
     * declaration of the operator of ()
     * @param m matrix
     * @return STRUCT digit
     */

    Digit operator()(Matrix &m);


private:
    /**
     * fields declaration
     */
    Dense _layer0;
    Dense _layer1;
    Dense _layer2;
    Dense _layer3;


};

#endif // MLPNETWORK_H
