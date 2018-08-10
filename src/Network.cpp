//
// Created by Wojtek on 2018-07-10.
//

#include <Network.h>

Network::Network(Layer* dataLayer, vector<Layer*> layers): dataLayer(dataLayer), layers(layers) {}

Network::~Network()
{
    delete dataLayer;

    del(layers);
}

string Network::toString()
{
    return "This network have "+ to_string(this->layers.size()) +" layers";
}