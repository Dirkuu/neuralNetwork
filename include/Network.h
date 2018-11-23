//
// Created by Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_NETWORK_H
#define NEURALNETWORK_NETWORK_H


#include "Layer.h"
#include <vector>

using namespace std;

class Network {
private:
    int epoch = 0;
    int maxNumbersOfEpochs = 5000;
    double learnRate = 1.0;

    shared_ptr<Layer> dataLayer;
    vector<shared_ptr<Layer>> hiddenLayers;
    shared_ptr<Layer> outputLayer;


    vector<double> wantedOutputs;

    void doUsefulThings();
    void goForward();
    void backPropagation();
    void newWeightsTime();
    double derivative(double sum);
public:
    Network(vector<shared_ptr<Input>> inputsForDataLayer, vector<int> numbersOfNeuronsInHiddenLayers, vector<double> wantedOutputs);



    //getters
    string log();
};

#endif //NEURALNETWORK_NETWORK_H