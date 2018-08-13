//
// Created by Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_LAYER_H
#define NEURALNETWORK_LAYER_H

using namespace std;

#include "Neuron.h"
#include "templateForeachDeleteFunction.h"
#include <vector>

class Layer {
private:
    vector<Neuron *> neurons;
    vector<double> outputs;
public:
    Layer(vector<Neuron*> neurons = vector<Neuron*>());
    ~Layer();
    //void addNeuron(Neuron *neuron);


//setters
    bool setNewInputsValues(vector<double> newInputsValues);


//getters
    Neuron* getNeuron(int index);
    vector<double> getOutputs();
    string toString();
};

#endif //NEURALNETWORK_LAYER_H
