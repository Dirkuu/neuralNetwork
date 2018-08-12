//
// Created by Wojtek on 2018-07-10.
//

using namespace std;

#include <Network.h>
#include <iostream>
//#include "csv.h"

Network::Network(Layer* dataLayer, vector<Layer*> layers): dataLayer(dataLayer), layers(layers) {}

Network::~Network()
{
    delete dataLayer;

    del(layers);
}

void Network::init(string pathToCSV)
{
    //io::CSVReader<4> in ("inputFile.csv");
    //in.read_header(io::ignore_extra_column, "vendor", "size", "speed");
    //string vendor;
    //int size;
    //double speed;
    //
    //while(in.read_row(vendor, size, speed))
    //{
    //    cout << vendor << endl << endl;
    //    cout << size<< endl << endl;
    //    cout << speed << endl << endl;
    //}
}

string Network::toString()
{
    return "This network have "+ to_string(this->layers.size()) +" layers";
}