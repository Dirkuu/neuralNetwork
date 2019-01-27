//
// Created by Wojtek on 2018-07-10.
//



#include <Network.h>
#include <iostream>
#include <ctime>

using namespace std;

int main ()
{
    srand(time(0));

    vector<shared_ptr<Input>> inputs;
    inputs.emplace_back(make_shared<Input>(1, 1));
    inputs.emplace_back(make_shared<Input>(0, 1));
    inputs.emplace_back(make_shared<Input>(0, 1));
    inputs.emplace_back(make_shared<Input>(0, 1));

    vector<int> numbersOfNeuronsInHiddenLayers;
    numbersOfNeuronsInHiddenLayers.emplace_back(2);

    vector<double> wantedOutputs;
    wantedOutputs.emplace_back(1);
    wantedOutputs.emplace_back(0);
    wantedOutputs.emplace_back(0);
    wantedOutputs.emplace_back(0);


    shared_ptr<Network> network = make_shared<Network>(inputs, numbersOfNeuronsInHiddenLayers, wantedOutputs, 1.0, 0.0);


    return 0;
}