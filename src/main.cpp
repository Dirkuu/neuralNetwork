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
    vector<double> inputsValues;
    inputsValues.push_back(1.0);
    inputsValues.push_back(1.0);
    inputsValues.push_back(1.0);
    inputsValues.push_back(5.0);

    Neuron* neuron = new Neuron(inputsValues);
    //Network *network = new Network();

    cout << neuron->sum();
    delete neuron;

    return 0;
}