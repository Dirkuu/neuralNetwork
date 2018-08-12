//
// Created by Wojtek on 2018-07-10.
//

using namespace std;

#include <Neuron.h>

Neuron::Neuron(double value, double weight)
{
    if (weight != NULL)         this->inputs.push_back(new Input(value, weight));
    else                        this->inputs.push_back(new Input(value));

    this->sum();
}

Neuron::Neuron(vector<Input*> inputs, Input* bias): bias(bias), inputs(inputs) { this->sum(); }

Neuron::~Neuron()
{
    if (this->bias != nullptr)          delete this->bias;

    del(inputs);
}

//void Neuron::addInput(Input *input)
//{
//    this->inputs.push_back(input);
//}

void Neuron::setNewBias(Input* newBias)
{
    delete this->bias;

    this->bias = newBias;
}

void Neuron::setNewInputs(vector<Input*> newInputs)
{
    if (this->inputs.size() == newInputs.size())
    {
        del(inputs);

        this->inputs = newInputs;
    }
}

Input* Neuron::getBias()
{
    return this->bias;
}

Input* Neuron::getInput(int index)
{
    this->inputs.at(index);
}

void Neuron::sum()
{
    double sum = 0;

    if (this->bias != nullptr)      sum += this->bias->getValue() * this->bias->getWeight();


    //for (int i = 0; i < this->inputs.size(); ++i)
    //{
    //    sum += this->inputs.at(i)->getValue() * this->inputs.at(i)->getWeight();
    //}

    for_each(this->inputs.begin(), this->inputs.end(), [&sum](Input* input){ sum += input->getValue() * input->getWeight(); });

    this->output = sum;
}

double Neuron::getError() { return this->error; }
//double Neuron::getSum() { return this->sum; }
double Neuron::getOutput() { return this->output; }
string Neuron::toString() { return "This neuron have "+ to_string(this->inputs.size()) +" inputs"; }
