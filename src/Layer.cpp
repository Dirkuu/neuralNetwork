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
    //for (int i = 0; i < this->neurons.at(0).getNumberOfInputs(); ++i)
    //{
    //    cout << "Current value: " << this->neurons.at(0).getInput(i).getValue() << endl;
    //}
    //cout << endl;
    //for (int i = 0; i < newInputsValues.size(); ++i)
    //{
    //    cout << "New value: " << newInputsValues.at(i) << endl;
    //}
    //cout << endl << endl;
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

vector<double> Layer::getDataLayerOutputs()
{
    vector<double> outputs;

    for (int i = 0; i < this->neurons.size(); ++i)
    {
        outputs.push_back(this->neurons.at(i).getOutput());
    }

    return outputs;
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
    vector<double> outputs = this->getDataLayerOutputs();

    string retString = "Number of neurons: ";
    retString += to_string(this->neurons.size());
    retString += ", outputs: ";

    for (int i = 0; i < this->getDataLayerOutputs().size(); ++i)
    {
        retString += " ";
        retString += to_string(outputs.at(i));
        retString += ";";
    }

    for (int i = 0; i < this->neurons.size(); ++i)
    {
        retString += "\nErrors: ";
        retString += to_string(this->getNeuron(i).getError());
        retString += ";";
    }

    retString += "\n";

    return retString;
}