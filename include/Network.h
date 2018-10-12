//
// Created by Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_NETWORK_H
#define NEURALNETWORK_NETWORK_H


#include "Layer.h"
#include <string>
#include <vector>

using namespace std;

class Network {
private:
    const double lerningRate = 0.1;
    Layer* dataLayer;
    vector<Layer> layers;
    Layer* outputLayer;
    vector<double> wantedOutputs;
    int epoch = 0;

    void doUsefulThings();
    void goForward();
    void backPropagation();
    double derivative(double sum);
public:
    Network(vector<Input> dataInputs, vector<int> numbersOfNeuronsInHiddenLayers, vector<double> wantedOutputs);
    Network(Layer* dataLayer, vector<Layer> layers);
    ~Network();

    void init(string pathToCSV);

    //Gettery
    string toString();
    string log();
};

#endif //NEURALNETWORK_NETWORK_H