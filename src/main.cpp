//
// Created by Wojtek on 2018-07-10.
//



#include <Network.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

int main (int argc, char *argv[])
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

    //
    if (argc == 4)                              unique_ptr<Network> network = make_unique<Network>(inputs, numbersOfNeuronsInHiddenLayers, wantedOutputs, atof(argv[1]), atof(argv[2]), atof(argv[3]));
    else if (argc == 3)                         unique_ptr<Network> network = make_unique<Network>(inputs, numbersOfNeuronsInHiddenLayers, wantedOutputs, atof(argv[1]), atof(argv[2]));
    else if (argc == 2)                         unique_ptr<Network> network = make_unique<Network>(inputs, numbersOfNeuronsInHiddenLayers, wantedOutputs, atof(argv[1]));
    else                                        unique_ptr<Network> network = make_unique<Network>(inputs, numbersOfNeuronsInHiddenLayers, wantedOutputs);



    return 0;
}