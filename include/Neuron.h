//
// Created gby Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_NEURON_H
#define NEURALNETWORK_NEURON_H

using namespace std;

#include "Input.h"
#include "templateForeachDeleteFunction.h"
#include <vector>
#include <string>
#include <bits/stdc++.h>

class Neuron {
private:
    double error;
    //double sum;
    double output;

    double sum();

    Input* bias;
    vector<Input *> inputs;
public:
    Neuron(double value, double weight = NULL);
    Neuron(vector<Input*> &inputs, Input* bias = nullptr);
    ~Neuron();
    //void addInput(Input *input);

    double activationFunction();








//setters
    void setNewBias(Input* newBias);
    bool setNewInputs(vector<Input*> newInputs);
    bool setNewInputsValues(vector<double> newInputsValues);
    bool setNewInputsWeights(vector<double> newInputsWeights);


//getters
    Input* getBias();
    Input* getInput(int index);

    double getError();
    //double getSum();
    double getOutput();
    string toString();
};

#endif //NEURALNETWORK_NEURON_H
