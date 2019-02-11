//
// Created by Wojtek on 2018-07-10.
//

#include <Network.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <stdio.h>

using namespace std;

Network::Network(vector<shared_ptr<Input>> inputsForDataLayer, vector<int> numbersOfNeuronsInHiddenLayers, vector<double> wantedOutputs, float learnRate, float momentum, float biasWeight): wantedOutputs(wantedOutputs), learnRate(learnRate), momentum(momentum)
{
    //delete file if exists
    remove(this->globalErrorFileName.c_str());

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
        this->hiddenLayers.emplace_back(make_shared<Layer>(numberOfNeurons, numbersOfInputs, biasWeight));
        numbersOfInputs = numberOfNeurons;
    }


    //outputLayer
    this->outputLayer = make_shared<Layer>(wantedOutputs.size(), numbersOfInputs);


    this->doUsefulThings();
}

void Network::doUsefulThings()
{
    //cout << this->log();




    this->goForward();
    this->backPropagation();
    this->newWeightsTime();

    if (this->epoch % this->savesFrequencyInEpochs == 0)    this->saveGlobalErrorToFile();

    ++this->epoch;

    for (this->epoch; this->epoch < this->maxNumbersOfEpochs && this->notWantedPrecision(); ++this->epoch)
    {
        //cout << this->log();




        this->goForward();
        this->backPropagation();
        this->newWeightsTime();

        if (this->epoch % this->savesFrequencyInEpochs == 0)    this->saveGlobalErrorToFile();
    }

    cout << this->log();
    cout << this->epoch << endl << "Global error: " << this->globalError() << endl;
}

bool Network::notWantedPrecision()
{
    for (shared_ptr<Neuron> outputLayerNeuron: this->outputLayer->getNeurons())     if (1.0 - fabs(outputLayerNeuron->getError()) < this->wantedPrecision)      return true;

    return false;
}

void Network::goForward()
{
    vector<shared_ptr<Neuron>> previousLayerNeurons = this->dataLayer->getNeurons();

    bool firstHiddenLayerFlag = true;
    //hiddenLayers forward
    for (shared_ptr<Layer> hiddenLayer: this->hiddenLayers)
    {
        if (firstHiddenLayerFlag)
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

            firstHiddenLayerFlag = false;
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
    //outputLayer
    int numberOfNeuron = 0;
    for (shared_ptr<Neuron> outputLayerNeuron: this->outputLayer->getNeurons())
    {
        outputLayerNeuron->setFutureError(this->wantedOutputs.at(numberOfNeuron) - outputLayerNeuron->getOutput());

        ++numberOfNeuron;
    }
    this->outputLayer->updateErrors();



    //hiddenLayers
    vector<shared_ptr<Neuron>> previousLayerNeurons = this->outputLayer->getNeurons();
    bool lastHiddenLayerFlag = true;

    for (auto hiddenLayerFromEnd = rbegin(this->hiddenLayers); hiddenLayerFromEnd != rend(this->hiddenLayers); ++hiddenLayerFromEnd)
    {
        auto& hiddenLayer = *hiddenLayerFromEnd;
        numberOfNeuron = 0;

        if (lastHiddenLayerFlag)
        {
            for (shared_ptr<Neuron> hiddenLayerFromEndNeuron: hiddenLayer->getNeurons())
            {
                double newError = 0;
                for (shared_ptr<Neuron> previousLayerNeuron: previousLayerNeurons)
                {
                    newError += previousLayerNeuron->getInputs().at(numberOfNeuron)->getWeight() * previousLayerNeuron->getError();
                }

                hiddenLayerFromEndNeuron->setFutureError(newError);

                ++numberOfNeuron;
            }
        }
        else
        {

        }
    }

    for (shared_ptr<Layer> hiddenLayer: this->hiddenLayers)
    {
        hiddenLayer->updateErrors();
    }
}

void Network::newWeightsTime()
{
    //hiddenLayers
    for (shared_ptr<Layer> hiddenLayer: this->hiddenLayers)
    {
        for (shared_ptr<Neuron> hiddenLayerNeuron: hiddenLayer->getNeurons())
        {
            double output = hiddenLayerNeuron->getOutput();

            for (shared_ptr<Input> hiddenLayerNeuronInput: hiddenLayerNeuron->getInputs())
            {
                double newWeight = hiddenLayerNeuronInput->getWeight() + (this->momentum * (hiddenLayerNeuronInput->getWeight() - hiddenLayerNeuronInput->getOutdatedWeight())) + (this->learnRate * hiddenLayerNeuron->getError() * this->derivative(output));
                hiddenLayerNeuronInput->setNewWeight(newWeight);
            }
        }
    }


    //outputLayer
    for (shared_ptr<Neuron> outputLayerNeuron: this->outputLayer->getNeurons())
    {
        double output = outputLayerNeuron->getOutput();

        for (shared_ptr<Input> outputLayerNeuronInput: outputLayerNeuron->getInputs())
        {
            double newWeight = outputLayerNeuronInput->getWeight() + (this->momentum * (outputLayerNeuronInput->getWeight() - outputLayerNeuronInput->getOutdatedWeight())) + (this->learnRate * outputLayerNeuron->getError() * this->derivative(output));
            outputLayerNeuronInput->setNewWeight(newWeight);
        }
    }
}

float Network::globalError()
{
    if (this->outputLayer->getNeurons().size() == this->wantedOutputs.size())
    {
        int index = 0;
        float temp,
        sum = 0;

        for (auto outputLayerNeuron: this->outputLayer->getNeurons())
        {
            temp = outputLayerNeuron->getOutput() - this->wantedOutputs.at(index);
            sum += temp * temp;
            ++index;
        }

        return sum;
    }

    return -1;
}

void Network::saveGlobalErrorToFile()
{
    ofstream globalError;
    globalError.open(this->globalErrorFileName, ios::app);
    globalError << "Epoch: " << this->epoch << "; Global error: " << this->globalError() << "\n";
    globalError.close();
}

double Network::derivative(double sum)
{
    return sum*(1 - sum);
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