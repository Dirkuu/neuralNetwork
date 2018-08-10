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

    Neuron* neuron = new Neuron(inputs);
    //Network *network = new Network();

    cout << "One neuron with random weights: " << neuron->sum();
    delete neuron;

    return 0;
}