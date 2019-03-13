//
// Created by Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_NETWORK_H
#define NEURALNETWORK_NETWORK_H


#include "Layer.h"
#include <vector>
#include <queue>

using namespace std;

class Network {
private:
    float wantedPrecision = 0.9; // *100%
    int epoch = 0;
    int maxNumbersOfEpochs = 4;
    float learnRate = 0.6;
    float momentum = 0.0;
    const int savesFrequencyInEpochs = 10;
    const string globalErrorFileName = "../globalError.txt";
    const string dataFileName = "../test.data";

    vector<pair<queue<double>, string>> data;

    shared_ptr<Layer> dataLayer;
    vector<shared_ptr<Layer>> hiddenLayers;
    shared_ptr<Layer> outputLayer;


    vector<double> wantedOutputs;

    void learnMode();

    void doUsefulThings();
    bool notWantedPrecision();
    void goForward();
    void backPropagation();
    void newWeightsTime();
    float globalError();
    void saveGlobalErrorToFile();
    double derivative(double sum);
    bool setNewWantedOutputs(vector<double>& newWantedOutputs);
    void mySubstr(string str, string delimiter, queue<string>& subStrings);
    void convertStringLineToObjects(string line);
    void copyDataFromFileToVariableThisData();
public:
    Network(vector<shared_ptr<Input>> inputsForDataLayer, vector<int> numbersOfNeuronsInHiddenLayers, vector<double> wantedOutputs, float learnRate = 1.0, float momentum = 0.0, float biasWeight = std::numeric_limits<float>::quiet_NaN());

    //setters
    bool setNewInputs(queue<double> newValues);
    bool setNewWantedOutputsByStringInput(string wantedOutput);

    //getters
    string log();
    string allOutputs();
};

#endif //NEURALNETWORK_NETWORK_H