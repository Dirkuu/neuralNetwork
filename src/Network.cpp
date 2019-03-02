//
// Created by Wojtek on 2018-07-10.
//

#include <Network.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <queue>
//#include <cstdlib>
#include <unordered_set>

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
    this->outputLayer = make_shared<Layer>(wantedOutputs.size(), numbersOfInputs, biasWeight);


    //cout << this->log();


    this->copyDataFromFileToVariableThisData();





    this->learnMode();


    queue<double> q;
    q.push(1);
    q.push(0);
    q.push(0);
    q.push(0);

    this->setNewInputs(q);
    this->setNewWantedOutputsByStringInput("i1000");
    //cout << this->log();
    this->goForward();
    cout << this->epoch << endl << "Global error: " << this->globalError() << endl;
    cout << this->allOutputs();

    q.pop();
    q.pop();
    q.pop();
    q.pop();
    q.push(0);
    q.push(1);
    q.push(0);
    q.push(0);

    this->setNewInputs(q);
    this->setNewWantedOutputsByStringInput("i0100");
    //cout << this->log();
    this->goForward();
    cout << this->epoch << endl << "Global error: " << this->globalError() << endl;
    cout << this->allOutputs();

    q.pop();
    q.pop();
    q.pop();
    q.pop();
    q.push(0);
    q.push(0);
    q.push(1);
    q.push(0);

    this->setNewInputs(q);
    this->setNewWantedOutputsByStringInput("i0010");
    //cout << this->log();
    this->goForward();
    cout << this->epoch << endl << "Global error: " << this->globalError() << endl;
    cout << this->allOutputs();

}

void Network::learnMode()
{
    unordered_set<int> dataIndexes;
    int temp;
    //<First iteration>
    for (int i = 0; i < this->data.size(); ++i)
    {
        do
        {
            temp = (int)(rand() % this->data.size());
        }
        while (!dataIndexes.emplace(temp).second);
    }

    for (int indexOfPair: dataIndexes)
    {
        this->setNewInputs(this->data.at(indexOfPair).first);
        this->setNewWantedOutputsByStringInput(this->data.at(indexOfPair).second);

        this->goForward();
        this->backPropagation();

        //If logs will be after newWeightsTime(), outputs from previous neurons will be diffrent from values of the next neurons
        cout << this->epoch << endl << "Global error: " << this->globalError() << endl;
        //cout << this->log();
        cout << this->allOutputs();

        this->newWeightsTime();
    }
    if (this->epoch % this->savesFrequencyInEpochs == 0)    this->saveGlobalErrorToFile();
    this->epoch++;
    //</First iteration>

    for (this->epoch; this->epoch < this->maxNumbersOfEpochs && this->notWantedPrecision(); ++this->epoch)
    {
//        cout << this->epoch << endl << "Global error: " << this->globalError() << endl;
//        cout << this->allOutputs();


        dataIndexes.clear();
        for (int i = 0; i < this->data.size(); ++i)
        {
            do
            {
                temp = (int)(rand() % this->data.size());
            }
            while (!dataIndexes.emplace(temp).second);
        }

        for (int indexOfPair: dataIndexes)
        {
            this->setNewInputs(this->data.at(indexOfPair).first);
            this->setNewWantedOutputsByStringInput(this->data.at(indexOfPair).second);

            this->goForward();
            this->backPropagation();

            //If logs will be after newWeightsTime(), outputs from previous neurons will be diffrent from values of the next neurons
            cout << this->epoch << endl << "Global error: " << this->globalError() << endl;
            //cout << this->log();
            cout << this->allOutputs();

            this->newWeightsTime();
        }

        if (this->epoch % this->savesFrequencyInEpochs == 0)    this->saveGlobalErrorToFile();
    }

    cout << this->epoch << endl << "Global error: " << this->globalError() << endl;
    //cout << this->log();
    cout << this->allOutputs();
}

void Network::doUsefulThings()
{
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
    for (shared_ptr<Neuron> outputLayerNeuron: this->outputLayer->getNeurons())
    {
//        cout << outputLayerNeuron->getError() << "\n";
//        cout << 1.0 - fabs(outputLayerNeuron->getError()) << "<" << this->wantedPrecision << "=" << (1.0 - fabs(outputLayerNeuron->getError()) < this->wantedPrecision) << "\n";
        if (1.0 - fabs(outputLayerNeuron->getError()) < this->wantedPrecision)      return true;
    }

    return false;
}

void Network::goForward()
{
    //for the first iteration, previous layer is data layer
    vector<shared_ptr<Neuron>> previousLayerNeurons = this->dataLayer->getNeurons();

    //hiddenLayers forward
    for (shared_ptr<Layer> hiddenLayer: this->hiddenLayers)
    {
        for (shared_ptr<Neuron> hiddenLayerNeuron: hiddenLayer->getNeurons())
        {
            int numberOfInput = 0;

            for (shared_ptr<Input> hiddenLayerNeuronInput: hiddenLayerNeuron->getInputs())
            {
                hiddenLayerNeuronInput->setNewValue(previousLayerNeurons.at(numberOfInput)->getOutput());//->getInputs().at(0)->getValue());

                ++numberOfInput;
            }
        }


        //for next iteration, previous layer will be current hidden layer
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



    //the loop below will calculate errors and layers will remember them
    //for first iteration, the previous layer is output layer
    vector<shared_ptr<Neuron>> previousLayerNeurons = this->outputLayer->getNeurons();

    for (auto hiddenLayerFromEnd = rbegin(this->hiddenLayers); hiddenLayerFromEnd != rend(this->hiddenLayers); ++hiddenLayerFromEnd)
    {
        auto& hiddenLayer = *hiddenLayerFromEnd;
        numberOfNeuron = 0;


        for (const shared_ptr<Neuron>& hiddenLayerFromEndNeuron: hiddenLayer->getNeurons())
        {
            double newError = 0;
            for (const shared_ptr<Neuron>& previousLayerNeuron: previousLayerNeurons)
            {
                newError += previousLayerNeuron->getInputs().at(numberOfNeuron)->getWeight() * previousLayerNeuron->getError();
            }

            hiddenLayerFromEndNeuron->setFutureError(newError);

            ++numberOfNeuron;
        }
        //and for future interation, previousLayer is current Layer
        previousLayerNeurons = hiddenLayer->getNeurons();
    }

    //now errors will really update
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

void Network::mySubstr(string str, string delimiter, queue<string>& subStrings)
{
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        subStrings.emplace(token);
        str.erase(0, pos + delimiter.length());
    }
    subStrings.emplace(str);
}

void Network::convertStringLineToObjects(string line)
{
    queue<double> newInputsValues;
    queue<string> subStrings;

    if (line != "")             this->mySubstr(line, ",", subStrings);

    while (!subStrings.empty())
    {
        switch(subStrings.front().at(0)) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                newInputsValues.emplace(stod(subStrings.front()));
                subStrings.pop();
                break;
            default:
                data.emplace_back(make_pair(newInputsValues, subStrings.front()));
                subStrings.pop();

                break;

        }
    }
}

void Network::copyDataFromFileToVariableThisData()
{
    ifstream irisDataFile;
    irisDataFile.open(this->dataFileName);
    string line;

    while (! irisDataFile.eof())
    {
        getline(irisDataFile, line);

        convertStringLineToObjects(line);
    }

    irisDataFile.close();
}




//Setters
bool Network::setNewWantedOutputs(vector<double>& newWantedOutputs)
{
    if (true)
    {
        this->wantedOutputs.clear();

        for (double newWantedOutput: newWantedOutputs)
        {
            this->wantedOutputs.emplace_back(newWantedOutput);
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool Network::setNewInputs(queue<double> newValues)
{
    if (this->dataLayer->getNeurons().size() == newValues.size())
    {
        for(shared_ptr<Neuron> dataNeuron: this->dataLayer->getNeurons())
        {
            dataNeuron->getInputs().at(0)->setNewValue(newValues.front());
            newValues.pop();
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool Network::setNewWantedOutputsByStringInput(string wantedOutput)
{
    vector<double> newWantedOutputs;

    if (wantedOutput == "Iris-setosa")
    {
        newWantedOutputs.emplace_back(1);
        newWantedOutputs.emplace_back(0);
        newWantedOutputs.emplace_back(0);
    }
    else if (wantedOutput == "Iris-versicolor")
    {
        newWantedOutputs.emplace_back(0);
        newWantedOutputs.emplace_back(1);
        newWantedOutputs.emplace_back(0);
    }
    else if (wantedOutput == "Iris-virginica")
    {
        newWantedOutputs.emplace_back(0);
        newWantedOutputs.emplace_back(0);
        newWantedOutputs.emplace_back(1);
    }
    else if (wantedOutput == "i1000")
    {
        newWantedOutputs.emplace_back(1);
        newWantedOutputs.emplace_back(0);
        newWantedOutputs.emplace_back(0);
        newWantedOutputs.emplace_back(0);
    }
    else if (wantedOutput == "i0100")
    {
        newWantedOutputs.emplace_back(0);
        newWantedOutputs.emplace_back(1);
        newWantedOutputs.emplace_back(0);
        newWantedOutputs.emplace_back(0);
    }
    else if (wantedOutput == "i0010")
    {
        newWantedOutputs.emplace_back(0);
        newWantedOutputs.emplace_back(0);
        newWantedOutputs.emplace_back(1);
        newWantedOutputs.emplace_back(0);
    }
    else if (wantedOutput == "i0001")
    {
        newWantedOutputs.emplace_back(0);
        newWantedOutputs.emplace_back(0);
        newWantedOutputs.emplace_back(0);
        newWantedOutputs.emplace_back(1);
    }

    return this->setNewWantedOutputs(newWantedOutputs);
}



//Getters
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

string Network::allOutputs ()
{
    string retString;

    retString = "Wanted outputs: ";
    retString += to_string(this->wantedOutputs.at(0)) + " ";
    retString += to_string(this->wantedOutputs.at(1)) + " ";
    retString += to_string(this->wantedOutputs.at(2)) + " ";
    retString += to_string(this->wantedOutputs.at(3)) + "\n";

    retString += "Real outputs:   ";
    retString += to_string(this->outputLayer->getNeurons().at(0)->getOutput()) + " ";
    retString += to_string(this->outputLayer->getNeurons().at(1)->getOutput()) + " ";
    retString += to_string(this->outputLayer->getNeurons().at(2)->getOutput()) + " ";
    retString += to_string(this->outputLayer->getNeurons().at(3)->getOutput()) + "\n";

    retString += "\n\n";

    return retString;
}