//
// Created by Wojtek on 2018-07-10.
//

#include <Layer.h>

using namespace std;

//TODO biasWeight
Layer::Layer(vector<shared_ptr<Neuron>> neurons, float biasWeight): neurons(neurons) {}

Layer::Layer(int numberOfNeurons, int numberOfInputs, float biasWeight)
{
    for(int i = 0; i < numberOfNeurons; ++i)
    {
        this->neurons.emplace_back(make_shared<Neuron>(numberOfInputs, biasWeight));
    }
}

void Layer::updateErrors()
{
    for (shared_ptr<Neuron> neuron: this->neurons)
    {
        neuron->updateError();
    }
}


//getters
vector<shared_ptr<Neuron>>& Layer::getNeurons()
{
    return this->neurons;
}

string Layer::toString()
{
    string retString = "This layer have "+ to_string(this->getNeurons().size()) +" neurons\n";

    for (shared_ptr<Neuron> neuron: this->neurons)
    {
        retString += "(Value / Weight / Output) of inputs\n";
        for (shared_ptr<Input> input: neuron->getInputs())
        {
            retString += to_string(input->getValue());
            retString += " / ";
            retString += to_string(input->getWeight());
            retString += " / ";
            retString += to_string(input->getOutput());
            retString += "\n";
        }

        retString += "Output of neuron: ";
        retString += to_string(neuron->getOutput());
        retString += "\n\n";
    }

    retString += "=================\n";

    return retString;
}