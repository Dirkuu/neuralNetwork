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
    vector<Input*> inputs;
    inputs.push_back(new Input(1.0));
    inputs.push_back(new Input(1.0));
    inputs.push_back(new Input(1.0));
    inputs.push_back(new Input(5.0));

    vector<Neuron*> neurons;
    neurons.push_back(new Neuron(inputs));
    neurons.push_back(new Neuron(inputs));

    Layer* layer = new Layer(neurons);


    //Network *network = new Network();

    //neurons.at(0)->sum();

    cout << "One neuron with random weights: " << neurons.at(0)->getOutput();
    delete layer;

    return 0;
}