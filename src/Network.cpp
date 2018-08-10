//
// Created by Wojtek on 2018-07-10.
//

#include <Network.h>
#include <Layer.h>
#include <iostream>

Network::Network(Layer* dataLayer, vector<Layer*> layers): dataLayer(dataLayer), layers(layers)
{
}

string Network::toString()
{
    return "This network have "+ to_string(this->layers.size()) +" layers";
}