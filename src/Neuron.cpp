//
// Created by Wojtek on 2018-07-10.
//

#include <Neuron.h>
#include <cmath>

using namespace std;

Neuron::Neuron(vector<shared_ptr<Input>> inputs, shared_ptr<Input> bias): inputs(inputs), bias(bias) {}
Neuron::Neuron(shared_ptr<Input> input, shared_ptr<Input> bias): bias(bias)
{
    this->inputs.emplace_back(input);
}
Neuron::Neuron(int numberOfInputs)
{
    for (int i = 0; i < numberOfInputs; ++i)
    {
        this->inputs.emplace_back(make_shared<Input>(0));
    }
}

void Neuron::updateError() { this->currentError = this->futureError; }

//setters
void Neuron::setError(double newError) { this->currentError = newError; }
void Neuron::setFutureError(double newFutureError) { this->futureError = newFutureError; }


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
    return 1.0 / (1.0 + exp(-this->sum() ));
}

double Neuron::getError()
{
    return this->currentError;
}

string Neuron::toString()
{
}