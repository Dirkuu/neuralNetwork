//
// Created by Wojtek on 2018-07-10.
//



#include <Network.h>
#include <iostream>

using namespace std;

int main ()
{
    srand(time(NULL));

    vector<Input> firstInputs;

    firstInputs.emplace_back(1.0);
    firstInputs.emplace_back(0.0);
    firstInputs.emplace_back(0.0);
    firstInputs.emplace_back(0.0);

    vector<Input> secondInputs;
    secondInputs.emplace_back(0.0);
    secondInputs.emplace_back(1.0);
    secondInputs.emplace_back(0.0);
    secondInputs.emplace_back(0.0);

    vector<Input> thirdInputs;
    thirdInputs.emplace_back(0.0);
    thirdInputs.emplace_back(0.0);
    thirdInputs.emplace_back(1.0);
    thirdInputs.emplace_back(0.0);

    vector<Input> fourthInputs;
    fourthInputs.emplace_back(0.0);
    fourthInputs.emplace_back(0.0);
    fourthInputs.emplace_back(0.0);
    fourthInputs.emplace_back(1.0);

    vector<int> numberOfNeuronsInHiddenLayers;
    numberOfNeuronsInHiddenLayers.emplace_back(2);

    Network* firstNetwork = new Network(firstInputs, 1, numberOfNeuronsInHiddenLayers);
    Network* secondNetwork = new Network(secondInputs, 1, numberOfNeuronsInHiddenLayers);
    Network* thirdNetwork = new Network(thirdInputs, 1, numberOfNeuronsInHiddenLayers);
    Network* fourthNetwork = new Network(fourthInputs, 1, numberOfNeuronsInHiddenLayers);

    delete firstNetwork;
    delete secondNetwork;
    delete thirdNetwork;
    delete fourthNetwork;


    return 0;
}