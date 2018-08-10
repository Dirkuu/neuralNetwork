//
// Created gby Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_NEURON_H
#define NEURALNETWORK_NEURON_H

using namespace std;

#include "Input.h"
#include <vector>
#include <string>

class Neuron {
private:
    Input* bias;
    vector<Input *> inputs;
public:
    Neuron(double value, double weight = NULL);
    Neuron(vector<Input*> inputs, Input* bias = nullptr);
    ~Neuron();
    //void addInput(Input *input);
    Input* getBias();
    Input* getInput(int index);

    double sum();

    string toString();
};

#endif //NEURALNETWORK_NEURON_H
