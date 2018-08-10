//
// Created by Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_NETWORK_H
#define NEURALNETWORK_NETWORK_H

using namespace std;

#include "Layer.h"
#include <string>
#include <vector>

const int defaultNumberOfLayers = 2;

class Network {
private:
    Layer *dataLayer;
    vector<Layer *> layers;
public:
    //  numberOfLayers is a int number without dataLayer
    Network(Layer* dataLayer, vector<Layer*> layers);

    string toString();
};

#endif //NEURALNETWORK_NETWORK_H