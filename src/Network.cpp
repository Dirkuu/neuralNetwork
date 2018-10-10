//
// Created by Wojtek on 2018-07-10.
//

#include <Network.h>

using namespace std;

Network::Network(vector<Input> dataInputs, int numberOfHiddenLayers, vector<int> numbersOfNeuronsInHiddenLayers)
{
    if (numberOfHiddenLayers == numbersOfNeuronsInHiddenLayers.size())
    {
        vector<Neuron> neuron;

        for (int i = 0; i < dataInputs.size(); ++i) {
            neuron.emplace_back(dataInputs.at(i).getValue(), dataInputs.at(i).getWeight());
        }

        this->dataLayer = new Layer(neuron);
        cout << endl << endl << this->dataLayer->toString() << endl;

        for (int i = 0; i < numberOfHiddenLayers; ++i)
        {
            this->layers.emplace_back(numbersOfNeuronsInHiddenLayers.at(i));
            cout << this->layers.at(i).toString() << endl;

        }

        this->outputLayer = new Layer(dataInputs.size());
        cout << this->outputLayer->toString() << endl;

        cout << endl << endl << "------------------------" << endl;
        //for_each (dataInputs.begin(), dataInputs.end(), [](vector<Input*> dataIpt){dataIpt;});
    }
    else
    {
        throw exception();
    }
}

Network::Network(Layer* dataLayer, vector<Layer> layers): dataLayer(dataLayer), layers(layers), outputLayer(new Layer(dataLayer->getNumberOfNeurons())) {}

Network::~Network()
{
    delete dataLayer;
    //delete layers;
    delete outputLayer;
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