//
// Created by Wojtek on 2018-07-10.
//

#include <Input.h>

using namespace std;

Input::Input(double value, double weight):      value(value), weight(weight) {}

double Input::getValue()
{
    return this->value;
}

double Input::getWeight()
{
    return this->weight;
}

void Input::setNewValue(double newValue)
{
    this->value = newValue;
}

void Input::setNewWeight(double newWeight)
{
    this->weight = newWeight;
}