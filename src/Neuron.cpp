//
// Created by Wojtek on 2018-07-10.
//

#include <Neuron.h>

using namespace std;

Neuron::Neuron(vector<shared_ptr<Input>> inputs, shared_ptr<Input> bias): inputs(inputs), bias(bias) {}




//getters
double Neuron::sum()
{
    double sum = 0;

    for (auto input: this->getInputs())
    {
        sum += input->getValue() * input->getWeight();
    }
    //TODO: Add bias


    return sum;
}

shared_ptr<Input> Neuron::getBias()
{
    return this->bias;
}

vector<shared_ptr<Input>>& Neuron::getInputs()
{
    return this->inputs;
}

double Neuron::getOutput()
{
    
}