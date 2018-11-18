//
// Created by Wojtek on 2018-07-10.
//

#include <Network.h>

using namespace std;



//Gettery
//string Network::toString()
//{
//    return "This network have "+ to_string(this->layers.size()) +" layers";
//}
//
//string Network::log()
//{
//    string retString = "Epoch: "+ to_string(this->epoch);
//    retString += "\n\n"+ this->dataLayer->toString() +"\n";
//
//    for (int i = 0; i < this->layers.size(); ++i)
//    {
//        retString += this->layers.at(i).toString() + "\n";
//    }
//
//    retString += this->outputLayer->toString() +"\n";
//
//    retString += "------------------------\n";
//
//    return retString;
//}