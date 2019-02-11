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
    float wantedPrecision = 0.9; // *100%
    int epoch = 0;
    int maxNumbersOfEpochs = 500;
    float learnRate = 1.0;
    float momentum = 1.0;
    const int savesFrequencyInEpochs = 1;
    string globalErrorFileName = "globalError.txt";

    shared_ptr<Layer> dataLayer;
    vector<shared_ptr<Layer>> hiddenLayers;
    shared_ptr<Layer> outputLayer;


    vector<double> wantedOutputs;

    void doUsefulThings();
    bool notWantedPrecision();
    void goForward();
    void backPropagation();
    void newWeightsTime();
    float globalError();
    void saveGlobalErrorToFile();
    double derivative(double sum);
public:
    Network(vector<shared_ptr<Input>> inputsForDataLayer, vector<int> numbersOfNeuronsInHiddenLayers, vector<double> wantedOutputs, float learnRate = 1.0, float momentum = 1.0, float biasWeight = std::numeric_limits<float>::quiet_NaN());



    //getters
    string log();
};

#endif //NEURALNETWORK_NETWORK_H