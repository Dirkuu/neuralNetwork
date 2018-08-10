//
// Created by Wojtek on 2018-07-10.
//

using namespace std;

#include <Neuron.h>

Neuron::Neuron(double value, double weight)
{
    if (weight != NULL)         this->inputs.push_back(new Input(value, weight));
    else                        this->inputs.push_back(new Input(value));
}

Neuron::Neuron(vector<Input*> inputs, Input *bias): bias(bias), inputs(inputs) {}

Neuron::~Neuron()
{
    if (this->bias != nullptr)          delete this->bias;

    for (int i = 0; i < this->inputs.size(); ++i)
    {
        delete this->inputs.at(i);
    }
}

//void Neuron::addInput(Input *input)
//{
//    this->inputs.push_back(input);
//}

Input* Neuron::getBias()
{
    return this->bias;
}

Input* Neuron::getInput(int index)
{
    this->inputs.at(index);
}

double Neuron::sum()
{
    double sum = 0;

    if (this->bias != nullptr)      sum += this->bias->getValue() * this->bias->getWeight();


    for (int i = 0; i < this->inputs.size(); ++i)
    {
        sum += this->inputs.at(i)->getValue() * this->inputs.at(i)->getWeight();
    }

    return sum;
}

string Neuron::toString()
{
    return "This neuron have "+ to_string(this->inputs.size()) +" inputs";
}
