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
    vector<shared_ptr<Input>> inputs;
public:
    vector<shared_ptr<Input>>& getInputs();
};

#endif //NEURALNETWORK_NEURON_H
