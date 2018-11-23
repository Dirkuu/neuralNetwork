//
// Created by Wojtek on 2018-07-10.
//

#include <Network.h>
#include <iostream>

using namespace std;

Network::Network(vector<shared_ptr<Input>> inputsForDataLayer, vector<int> numbersOfNeuronsInHiddenLayers, vector<double> wantedOutputs): wantedOutputs(wantedOutputs)
{
    //dataLayer
    vector<shared_ptr<Neuron>> neuronsInDataLayer;

    for (auto inputForDataLayer: inputsForDataLayer)
    {
        neuronsInDataLayer.emplace_back(make_shared<Neuron>(inputForDataLayer));
    }

    this->dataLayer = make_shared<Layer>(neuronsInDataLayer);


    //hiddenLayers
    int numbersOfInputs = this->dataLayer->getNeurons().size();

    for (int numberOfNeurons: numbersOfNeuronsInHiddenLayers)
    {
        this->hiddenLayers.emplace_back(make_shared<Layer>(numberOfNeurons, numbersOfInputs));
        numbersOfInputs = numberOfNeurons;
    }


    //outputLayer
    this->outputLayer = make_shared<Layer>(wantedOutputs.size(), numbersOfInputs);


    this->doUsefulThings();
}

void Network::doUsefulThings()
{
    for (this->epoch; this->epoch < this->maxNumbersOfEpochs; ++this->epoch)
    {
        cout << this->log();

        this->goForward();
        this->backPropagation();
    }


    cout << fixed << this->log();
}

void Network::goForward()
{
    vector<shared_ptr<Neuron>> previousLayerNeurons = this->dataLayer->getNeurons();

    bool firstHiddenlayer = true;
    //hiddenLayers forward
    for (shared_ptr<Layer> hiddenLayer: this->hiddenLayers)
    {
        if (firstHiddenlayer)
        {
            for (shared_ptr<Neuron> hiddenLayerNeuron: hiddenLayer->getNeurons())
            {
                int numberOfInput = 0;

                for (shared_ptr<Input> hiddenLayerNeuronInput: hiddenLayerNeuron->getInputs())
                {
                    hiddenLayerNeuronInput->setNewValue(previousLayerNeurons.at(numberOfInput)->getInputs().at(0)->getValue());

                    ++numberOfInput;
                }
            }

            firstHiddenlayer = false;
        }
        else
        {
            for (shared_ptr<Neuron> hiddenLayerNeuron: hiddenLayer->getNeurons())
            {
                int numberOfInput = 0;

                for (shared_ptr<Input> hiddenLayerNeuronInput: hiddenLayerNeuron->getInputs())
                {
                    hiddenLayerNeuronInput->setNewValue(previousLayerNeurons.at(numberOfInput)->getOutput());

                    ++numberOfInput;
                }
            }
        }

        previousLayerNeurons = hiddenLayer->getNeurons();
    }

    //outputLayer forward
    for (shared_ptr<Neuron> outputLayerNeuron: this->outputLayer->getNeurons())
    {
        int numberOfInput = 0;

        for (shared_ptr<Input> outputLayerNeuronInput: outputLayerNeuron->getInputs())
        {
            outputLayerNeuronInput->setNewValue(previousLayerNeurons.at(numberOfInput)->getOutput());

            ++numberOfInput;
        }
    }
}

void Network::backPropagation()
{
    int numberOfNeuron = 0;
    for (shared_ptr<Neuron> outputLayerNeuron: this->outputLayer->getNeurons())
    {
        outputLayerNeuron->setFutureError(this->wantedOutputs.at(numberOfNeuron) - outputLayerNeuron->getOutput());

        ++numberOfNeuron;
    }




    this->outputLayer->updateErrors();
}

void Network::newWeightsTime()
{
    for (shared_ptr<Neuron> outputLayerNeuron: this->outputLayer->getNeurons())
    {
        for (shared_ptr<Input> outputLayerNeuronInput: outputLayerNeuron->getInputs())
        {
            double newWeight = outputLayerNeuronInput->getWeight() + (this->learnRate * outputLayerNeuron->getError());
            outputLayerNeuronInput->setNewWeight();
        }
    }
}




//Gettery
//string Network::toString()
//{
//    return "This network have "+ to_string(this->layers.size()) +" layers";
//}
//
string Network::log()
{
    string retString = "Epoch: "+ to_string(this->epoch);
    retString += "\n\n"+ this->dataLayer->toString() +"\n";

    for (shared_ptr<Layer> hiddenLayer: this->hiddenLayers)
    {
        retString += hiddenLayer->toString() + "\n";
    }

    retString += this->outputLayer->toString() +"\n";

    return retString;
}