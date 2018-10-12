//
// Created by Wojtek on 2018-07-10.
//

#include <Network.h>

using namespace std;

Network::Network(vector<Input> dataInputs, vector<int> numbersOfNeuronsInHiddenLayers, vector<double> wantedOutputs): wantedOutputs(wantedOutputs)
{
    vector<Neuron> neuron;

    for (int i = 0; i < dataInputs.size(); ++i) {
        neuron.emplace_back(dataInputs.at(i).getValue(), dataInputs.at(i).getWeight());
    }

    this->dataLayer = new Layer(neuron);

    for (int i = 0; i < numbersOfNeuronsInHiddenLayers.size(); ++i)
    {
        this->layers.emplace_back(numbersOfNeuronsInHiddenLayers.at(i));

    }

    this->outputLayer = new Layer(dataInputs.size());

    cout << this->log();
    this->doUsefulThings();
}

Network::Network(Layer* dataLayer, vector<Layer> layers): dataLayer(dataLayer), layers(layers), outputLayer(new Layer(dataLayer->getNumberOfNeurons())) {}

Network::~Network()
{
    delete dataLayer;
    //delete layers;
    delete outputLayer;
}

void Network::doUsefulThings()
{
    if (this->epoch < 70000)
    {
        this->layers.at(0).setNewInputsValues(this->dataLayer->getDataLayerOutputs());
        this->goForward();

        this->backPropagation();

        ++this->epoch;
        cout << this->log();
        this->doUsefulThings();
    }
}

void Network::goForward()
{
    //this->layers.at(0).setNewInputsValues(this->dataLayer->getDataLayerOutput());

    if (this->layers.size() > 1)
    {
        for (int i = 1; i < this->layers.size(); ++i)
        {
            this->layers.at(i).setNewInputsValues(this->layers.at(i - 1).getOutputs());
        }
    }

    this->outputLayer->setNewInputsValues(this->layers.at(this->layers.size() - 1).getOutputs());

    for (int neuronIndex = 0; neuronIndex < this->outputLayer->getNumberOfNeurons(); ++neuronIndex)
    {
        this->outputLayer->getNeuron(neuronIndex).activationFunction();
    }
}

void Network::backPropagation()
{
    //neurons in outputLayer
    for (int neuronIndex = 0; neuronIndex < this->outputLayer->getNumberOfNeurons(); ++neuronIndex)
    {
        vector<double> newWeights;
        //inputs in neurons
        for (int inputIndex = 0; inputIndex < this->outputLayer->getNeuron(neuronIndex).getNumberOfInputs(); ++inputIndex)
        {
            double error = this->derivative(this->outputLayer->getNeuron(neuronIndex).getSum());
            error *= (this->outputLayer->getNeuron(neuronIndex).getOutput() - this->wantedOutputs.at(inputIndex));
            this->outputLayer->getNeuron(neuronIndex).setError(error);



            newWeights.emplace_back(this->outputLayer->getNeuron(neuronIndex).getInput(inputIndex).getWeight() + (error * this->outputLayer->getNeuron(neuronIndex).getInput(inputIndex).getValue()));
        }

        this->outputLayer->getNeuron(neuronIndex).setNewInputsWeights(newWeights);
    }

    //hiddenLayers
    for (int layerIndex = (int)this->layers.size() - 1; layerIndex > -1; --layerIndex)
    {
        if (layerIndex == (int)this->layers.size() - 1)
        {
            //neurons in !last hiddenLayer!
            for (int hiddenLayerNeuronIndex = 0; hiddenLayerNeuronIndex < this->layers.at(layerIndex).getNumberOfNeurons(); ++hiddenLayerNeuronIndex)
            {
                vector<double> newWeights;
                //inputs of neuron in !last hiddenLayer!
                for (int inputIndex = 0; inputIndex < this->layers.at(layerIndex).getNeuron(hiddenLayerNeuronIndex).getNumberOfInputs(); ++inputIndex)
                {
                    double error = this->derivative(this->layers.at(layerIndex).getNeuron(hiddenLayerNeuronIndex).getSum());
                    //neurons in !outputLayer!
                    for (int outputLayerNeuronIndex = 0; outputLayerNeuronIndex < this->outputLayer->getNumberOfNeurons(); ++outputLayerNeuronIndex)
                    {
                        //errors * weights
                        error *= this->outputLayer->getNeuron(hiddenLayerNeuronIndex).getError();
                        error *= this->outputLayer->getNeuron(hiddenLayerNeuronIndex).getInput(hiddenLayerNeuronIndex).getValue();
                    }

                    this->layers.at(layerIndex).getNeuron(hiddenLayerNeuronIndex).setError(error);

                    newWeights.emplace_back(this->layers.at(layerIndex).getNeuron(hiddenLayerNeuronIndex).getInput(inputIndex).getWeight() + (error * this->layers.at(layerIndex).getNeuron(hiddenLayerNeuronIndex).getInput(inputIndex).getValue()));
                }

                this->layers.at(layerIndex).getNeuron(hiddenLayerNeuronIndex).setNewInputsWeights(newWeights);
            }
        }
        else
        {
            ////neuron in hiddenLayers
            //for (int neuronIndex = 0; neuronIndex < this->layers.at(layerIndex).getNumberOfNeurons(); ++neuronIndex)
            //{
            //    vector<double> newWeights;
            //    for (int inputIndex = 0; inputIndex < this->layers.at(layerIndex).getNeuron(neuronIndex).getNumberOfInputs())
            //    {
            //        double error = this->layers.at(layerIndex).getNeuron(neuronIndex).getInput(inputIndex).getValue();
            //        error *= (this->layers.at(layerIndex).getNeuron(neuronIndex).getOutput() - this->wantedOutputs)
            //    }
            //}
        }
    }

    ////neurons in dataLayer
    //for (int neuronIndex = 0; neuronIndex< this->dataLayer->getNumberOfNeurons(); ++neuronIndex)
    //{
    //    vector<double> newWeights;
    //    //inputs of neuron in !dataLayer!
    //    for (int inputIndex = 0; inputIndex < this->dataLayer->getNeuron(neuronIndex).getNumberOfInputs(); ++inputIndex)
    //    {
    //        double error = this->derivative(this->dataLayer->getNeuron(neuronIndex).getSum());
    //        //neurons in !first hiddenLayer!
    //        for (int hiddenLayerNeuronIndex = 0; hiddenLayerNeuronIndex < this->layers.at(0).getNumberOfNeurons(); ++hiddenLayerNeuronIndex)
    //        {
    //            //errors * weights
    //            error *= this->layers.at(0).getNeuron(hiddenLayerNeuronIndex).getError();
    //            error *= this->layers.at(0).getNeuron(hiddenLayerNeuronIndex).getInput(neuronIndex).getWeight();
    //        }
    //
    //        this->dataLayer->getNeuron(neuronIndex).setError(error);
    //
    //        newWeights.emplace_back(error * this->dataLayer->getNeuron(neuronIndex).getInput(inputIndex).getValue());
    //    }
    //
    //    this->dataLayer->getNeuron(neuronIndex).setNewInputsWeights(newWeights);
    //}
}

double Network::derivative(double sum)
{
    return sum*(1 - sum);
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


//Gettery
string Network::toString()
{
    return "This network have "+ to_string(this->layers.size()) +" layers";
}

string Network::log()
{
    string retString = "Epoch: "+ to_string(this->epoch);
    retString += "\n\n"+ this->dataLayer->toString() +"\n";

    for (int i = 0; i < this->layers.size(); ++i)
    {
        retString += this->layers.at(i).toString() + "\n";
    }

    retString += this->outputLayer->toString() +"\n";

    retString += "------------------------\n";

    return retString;
}