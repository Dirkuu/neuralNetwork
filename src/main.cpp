//
// Created by Wojtek on 2018-07-10.
//


using namespace std;

#include <Network.h>
#include <iostream>

int main ()
{
    srand(time(NULL));
    //Input *input = new Input(5);
    vector<Input*> firstInputs;
    firstInputs.push_back(new Input(1.0));
    firstInputs.push_back(new Input(1.0));
    firstInputs.push_back(new Input(1.0));
    firstInputs.push_back(new Input(2.0));

    vector<Input*> secondInputs;
    secondInputs.push_back(new Input(1.0));
    secondInputs.push_back(new Input(1.0));
    secondInputs.push_back(new Input(1.0));
    secondInputs.push_back(new Input(2.0));

    vector<Neuron*> neurons;
    neurons.push_back(new Neuron(firstInputs, new Input(1.2)));
    neurons.push_back(new Neuron(secondInputs));

    Layer* layer = new Layer(neurons);


    //Network *network = new Network();

    //neurons.at(0)->sum();
    //cout << neurons.at(0)->activationFunction();
    cout << layer->toString();
    delete layer;

    return 0;
}