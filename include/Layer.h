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
    Layer(vector<shared_ptr<Neuron>> neurons, float biasWeight = std::numeric_limits<float>::quiet_NaN());
    Layer(int numberOfNeurons, int numberOfInputs, float biasWeight = std::numeric_limits<float>::quiet_NaN());

    void updateErrors();


    //getters
    vector<shared_ptr<Neuron>>& getNeurons();

    string toString();
};

#endif //NEURALNETWORK_LAYER_H
