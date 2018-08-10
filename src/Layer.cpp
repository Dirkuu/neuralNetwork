//
// Created by Wojtek on 2018-07-10.
//

#include <Neuron.h>
#include <Layer.h>
#include <string>
#include <iostream>

Layer::Layer(vector<Neuron*> neurons): neurons(neurons)
{
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