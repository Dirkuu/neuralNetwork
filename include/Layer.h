//
// Created by Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_LAYER_H
#define NEURALNETWORK_LAYER_H


#include "Neuron.h"
#include <vector>

using namespace std;

class Layer {
private:
    vector<Neuron> neurons;
    vector<double> outputs;
public:
    Layer(int numberOfNeurons);
    Layer(vector<Neuron> neurons = vector<Neuron>());
    ~Layer();
    //void addNeuron(Neuron *neuron);


//setters
    bool setNewInputsValues(vector<double> newInputsValues);


//getters
    Neuron& getNeuron(int index);
    vector<double> getDataLayerOutputs();
    vector<double> getOutputs();
    int getNumberOfNeurons();
    string toString();
};

#endif //NEURALNETWORK_LAYER_H
