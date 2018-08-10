//
// Created by Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_LAYER_H
#define NEURALNETWORK_LAYER_H

using namespace std;

#include "Neuron.h"
#include <vector>

class Layer {
private:
    vector<Neuron *> neurons;
public:
    Layer(int numberOfNeurons = 3, vector<double> inputsValues = vector<double>());
    void addNeuron(Neuron *neuron);

    Neuron* getNeuron(int index);

    string toString();
};

#endif //NEURALNETWORK_LAYER_H
