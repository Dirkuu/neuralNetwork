//
// Created by Wojtek on 2018-07-10.
//

#include <Neuron.h>
#include <tgmath.h>

using namespace std;

double Neuron::sum()
{
    double sum = 0;

    if (this->bias != nullptr)      sum += this->bias->getValue() * this->bias->getWeight();


    //for (int i = 0; i < this->inputs.size(); ++i)
    //{
    //    sum += this->inputs.at(i)->getValue() * this->inputs.at(i)->getWeight();
    //}

    //for_each(this->inputs.begin(), this->inputs.end(), [&sum](Input* input){ sum += input->getValue() * input->getWeight(); });

    for (int i = 0; i < this->inputs.size(); ++i)
    {
        sum += this->inputs.at(i).getValue() * this->inputs.at(i).getWeight();
    }

    return sum;
}

Neuron::Neuron(double value, double weight, Input* bias): bias(bias)
{
    if (weight == NULL)         this->inputs.emplace_back(value);
    else                        this->inputs.emplace_back(value, weight);


    this->sum();
}

Neuron::Neuron(vector<Input> inputs, Input* bias): bias(bias), inputs(inputs) { this->sum(); }

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
    this->output = 1.0 / (1.0 + exp(- this->sum() ));
    return this->output;
}








//setters
void Neuron::setNewBias(Input* newBias)
{
    delete this->bias;

    this->bias = newBias;
}

bool Neuron::setNewInputs(vector<Input> newInputs)
{
    if (this->inputs.size() == newInputs.size())
    {
        //delete inputs;//del(inputs);

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
        return false;
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

double Neuron::getError() { return this->error; }
//double Neuron::getSum() { return this->sum; }
double Neuron::getOutput() { return this->output; }
string Neuron::toString() { return "This neuron have "+ to_string(this->inputs.size()) +" inputs"; }
