//
// Created by Wojtek on 2018-07-10.
//

#include <Neuron.h>
#include <Network.h>
#include <tgmath.h>

using namespace std;

double Neuron::sumFunction()
{
    double sum = 0;

    if (this->bias != nullptr)      sum += this->bias->getValue() * this->bias->getWeight();


    for (int i = 0; i < this->inputs.size(); ++i)
    {
        sum += this->inputs.at(i).getValue() * this->inputs.at(i).getWeight();
    }

    this->sum = sum;

    return this->sum;
}

Neuron::Neuron(double value, double weight, Input* bias): bias(bias)
{
    if (weight == NULL)         this->inputs.emplace_back(value);
    else                        this->inputs.emplace_back(value, weight);

    this->output = value;
    this->sumFunction();
}

Neuron::Neuron(vector<Input> inputs, Input* bias): bias(bias), inputs(inputs) { this->sumFunction(); }

Neuron::~Neuron()
{
    if (this->bias != nullptr)          delete this->bias;

    //del(inputs);
}

//void Neuron::addInput(Input *input)
//{
//    this->inputs.push_back(input);
//}

double Neuron::activationFunction()
{
    this->output = 1.0 / (1.0 + exp(-this->sumFunction() ));
    return this->output;
}








//setters
void Neuron::setWantedOutput(double wantedOutput) { this->wantedOutput = wantedOutput; }

void Neuron::setError(double error) { this->error = error; }

void Neuron::setNewBias(Input* newBias)
{
    delete this->bias;

    this->bias = newBias;
}

bool Neuron::setNewInputs(vector<Input> newInputs)
{
    if (this->inputs.size() == newInputs.size())
    {
        this->inputs = newInputs;

        return true;
    }
    else
    {
        return false;
    }
}

bool Neuron::setNewInputsValues(vector<double> newInputsValues)
{
    //cout << "Liczba wejsc: " << this->inputs.size() << endl;
    //cout << "Nowa liczba wejsc: " << newInputsValues.size() << endl;
    if (this->inputs.size() == newInputsValues.size())
    {
        for (int i = 0; i < this->inputs.size(); ++i)
        {
            this->inputs.at(i).setNewValue(newInputsValues.at(i));
        }

        return true;
    }
    else
    {
        this->inputs.clear();

        for (int i = 0; i < newInputsValues.size(); ++i)
        {
            this->inputs.emplace_back(newInputsValues.at(i));
        }

        return this->setNewInputsValues(newInputsValues);
    }
}

bool Neuron::setNewInputsWeights(vector<double> newInputsWeights)
{
    if (this->inputs.size() == newInputsWeights.size())
    {
        for (int i = 0; i < this->inputs.size(); ++i)
        {
            this->inputs.at(i).setNewWeight(newInputsWeights.at(i));
        }

        return true;
    }
    else
    {
        return false;
    }
}



//getters
Input* Neuron::getBias()
{
    return this->bias;
}

Input& Neuron::getInput(int index)
{
    return this->inputs.at(index);
}

int Neuron::getNumberOfInputs() { return this->inputs.size(); }

double Neuron::getError()
{
    return this->error;
}
double Neuron::getSum() { return this->sum; }
double Neuron::getOutput() { return this->output; }
double Neuron::getWantedOutput() { return this->wantedOutput; }
string Neuron::toString() { return "This neuron have "+ to_string(this->inputs.size()) +" inputs"; }
