//
// Created by Wojtek on 2018-07-10.
//

#include <Neuron.h>
#include <cmath>

using namespace std;

Neuron::Neuron(vector<shared_ptr<Input>> inputs, float biasWeight): inputs(inputs)
{
    this->createBias(biasWeight);
}
Neuron::Neuron(shared_ptr<Input> input, float biasWeight)
{
    this->inputs.emplace_back(input);

    this->createBias(biasWeight);
}
Neuron::Neuron(int numberOfInputs, float biasWeight)
{
    for (int i = 0; i < numberOfInputs; ++i)
    {
        this->inputs.emplace_back(make_shared<Input>(0));
    }

    this->createBias(biasWeight);
}

void Neuron::updateError() { this->currentError = this->futureError; }

void Neuron::createBias(float biasWeight)
{
    if (isnan(biasWeight))      this->bias = nullptr;
    else                        this->bias = make_shared<Input>(1, biasWeight);
}

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

    if (this->bias != nullptr)      sum += this->bias->getValue() * this->bias->getWeight();


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