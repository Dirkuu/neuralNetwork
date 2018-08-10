//
// Created by Wojtek on 2018-07-10.
//

#include <Neuron.h>
#include <Layer.h>
#include <string>
#include <iostream>

Layer::Layer(int numberOfNeurons, vector<double> inputsValues)
{
    if (inputsValues.size() != 0)
    {
        for (int i = 0; i < numberOfNeurons; ++i)
        {
            this->neurons.push_back(new Neuron(inputsValues));
        }
    }
    else
    {
        for (int i = 0; i < numberOfNeurons; ++i)
        {
            this->neurons.push_back(new Neuron(1));
        }
    }
}

void Layer::addNeuron(Neuron *neuron)
{
    this->neurons.push_back(neuron);
}

Neuron* Layer::getNeuron(int index)
{
    return this->neurons.at(index);
}

string Layer::toString()
{
    return "This layer have "+ to_string(this->neurons.size()) +" neurons";
}