//
// Created by Wojtek on 2018-07-10.
//


using namespace std;

#include <Network.h>
#include <iostream>

using std::vector;

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


    cout << layer->toString();


    delete layer;





    //vector<Input*> inputs;
    //inputs.push_back(new Input(5));
    //inputs.push_back(new Input(2));
//
    //Neuron* neuron = new Neuron(inputs);
//
    //for (int i = 0; i < inputs.size(); ++i)
    //{
    //    cout << inputs.at(i)->getValue() << "; " << neuron->getInput(i)->getValue() << endl;
    //}
//
    //delete neuron;
    //delete inputs.at(0);
    //delete inputs.at(1);

    return 0;
}