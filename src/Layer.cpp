//
// Created by Wojtek on 2018-07-10.
//

#include <Layer.h>

using namespace std;

Layer::Layer(vector<shared_ptr<Neuron>> neurons): neurons(neurons) {}

Layer::Layer(int numberOfNeurons, int numberOfInputs)
{
    for(int i = 0; i < numberOfNeurons; ++i)
    {
        this->neurons.emplace_back(make_shared<Neuron>(numberOfInputs));
    }
}



//getters
vector<shared_ptr<Neuron>>& Layer::getNeurons()
{
    return this->neurons;
}