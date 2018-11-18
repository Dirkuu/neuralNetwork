//
// Created by Wojtek on 2018-07-10.
//

#include <Neuron.h>

using namespace std;

vector<shared_ptr<Input>>& Neuron::getInputs()
{
    return this->inputs;
}