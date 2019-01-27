//
// Created gby Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_NEURON_H
#define NEURALNETWORK_NEURON_H


#include "Input.h"
#include <vector>
#include <memory>
#include <limits>

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
    void createBias(float biasWeight);
public:
    Neuron(vector<shared_ptr<Input>> inputs, float biasWeight = std::numeric_limits<float>::quiet_NaN());
    Neuron(shared_ptr<Input> input, float biasWeight = std::numeric_limits<float>::quiet_NaN());
    Neuron(int numberOfInputs, float biasWeight = std::numeric_limits<float>::quiet_NaN());

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
