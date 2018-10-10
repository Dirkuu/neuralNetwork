//
// Created by Wojtek on 2018-07-10.
//

#include <Layer.h>

using namespace std;

Layer::Layer(int numberOfNeurons)
{
    vector<Neuron> neurons;

    for (int i = 0; i < numberOfNeurons; ++i)
    {
        neurons.emplace_back(0.0);
    }

    this->neurons = neurons;
}
Layer::Layer(vector<Neuron> neurons): neurons(neurons) {}

Layer::~Layer()
{
    //del(neurons);
}

//void Layer::addNeuron(Neuron *neuron)
//{
//    this->neurons.push_back(neuron);
//}







//setters
bool Layer::setNewInputsValues(vector<double> newInputsValues)
{
    for (int i = 0; i < this->neurons.size(); ++i)
    {
        if (!this->neurons.at(i).setNewInputsValues(newInputsValues))          return false;
    }


    return true;
}





//getters
Neuron& Layer::getNeuron(int index)
{
    return this->neurons.at(index);
}

vector<double> Layer::getOutputs()
{
    vector<double> outputs;

    for (int i = 0; i < this->neurons.size(); ++i)
    {
        outputs.push_back(this->neurons.at(i).activationFunction());
    }

    return outputs;
}

int Layer::getNumberOfNeurons()
{
    return this->neurons.size();
}

string Layer::toString()
{
    vector<double> outputs = this->getOutputs();

    string retString = "Number of neurons: ";
    retString += to_string(this->neurons.size());
    retString += ", outputs: ";

    for (int i = 0; i < this->getOutputs().size(); ++i)
    {
        retString += " ";
        retString += to_string(outputs.at(i));
        retString += ";";
    }

    retString += "\n";

    return retString;
}