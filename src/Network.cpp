//
// Created by Wojtek on 2018-07-10.
//

#include <Network.h>
#include <Layer.h>
#include <iostream>

Network::Network(vector<double> inputsValues, int numberOfLayers): dataLayer(new Layer(inputsValues))
{
    for (int i = 0; i < numberOfLayers; ++i)
    {
        this->layers.push_back(new Layer(inputsValues));
    }
}

string Network::toString()
{
    return "This network have "+ to_string(this->layers.size()) +" layers";
}