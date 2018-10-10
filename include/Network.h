//
// Created by Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_NETWORK_H
#define NEURALNETWORK_NETWORK_H


#include "Layer.h"
#include "templateForeachDeleteFunction.h"
#include <string>
#include <vector>

using namespace std;

class Network {
private:
    Layer* dataLayer;
    vector<Layer> layers;
    Layer* outputLayer;
public:
    Network(vector<Input> dataInputs, int numberOfHiddenLayers, vector<int> numbersOfNeuronsInHiddenLayers);
    Network(Layer* dataLayer, vector<Layer> layers);
    ~Network();

    void init(string pathToCSV);
    string toString();
};

#endif //NEURALNETWORK_NETWORK_H