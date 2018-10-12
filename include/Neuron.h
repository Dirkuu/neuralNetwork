//
// Created gby Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_NEURON_H
#define NEURALNETWORK_NEURON_H


#include "Input.h"
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <cstddef>

using namespace std;

class Neuron {
private:
    double error;
    double sum;
    double output;
    double wantedOutput = NULL;

    double sumFunction();

    Input* bias;
    vector<Input> inputs;
public:
    Neuron(double value = 0, double weight = NULL, Input* bias = nullptr);
    Neuron(vector<Input> inputs, Input* bias = nullptr);
    ~Neuron();
    //void addInput(Input *input);

    double activationFunction();








//setters
    void setWantedOutput(double wantedOutput);
    void setError(double error);
    void setNewBias(Input* newBias);
    bool setNewInputs(vector<Input> newInputs);
    bool setNewInputsValues(vector<double> newInputsValues);
    bool setNewInputsWeights(vector<double> newInputsWeights);


//getters
    Input* getBias();
    Input& getInput(int index);

    int getNumberOfInputs();

    double getError();
    double getSum();
    double getOutput();
    double getWantedOutput();
    string toString();
};

#endif //NEURALNETWORK_NEURON_H
