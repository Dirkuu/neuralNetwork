//
// Created gby Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_NEURON_H
#define NEURALNETWORK_NEURON_H


#include "Input.h"
#include <vector>
#include <memory>

using namespace std;

class Neuron {
private:
    shared_ptr<Input> bias;
    vector<shared_ptr<Input>> inputs;
    double currentError;
    double futureError;

    //setters
    void setError(double newError);

    //getters
    double sum();
public:
    Neuron(vector<shared_ptr<Input>> inputs, shared_ptr<Input> bias = nullptr);
    Neuron(shared_ptr<Input> input, shared_ptr<Input> bias = nullptr);
    Neuron(int numberOfInputs);

    void updateError();

    //setters
    void setFutureError(double newFutureError);

    //getters
    shared_ptr<Input> getBias();
    vector<shared_ptr<Input>>& getInputs();
    double getOutput();
    double getError();

    string toString();
};

#endif //NEURALNETWORK_NEURON_H
