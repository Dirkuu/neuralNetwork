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
    vector<shared_ptr<Neuron>> neurons;
public:
    Layer(vector<shared_ptr<Input>> inputs);
    Layer(int numberOfNeurons, int numberOfInputs);


    //getters
    vector<shared_ptr<Neuron>>& getNeurons();
};

#endif //NEURALNETWORK_LAYER_H
