//
// Created by Wojtek on 2018-07-10.
//

#ifndef NEURALNETWORK_INPUT_H
#define NEURALNETWORK_INPUT_H

#include <cstdlib>

class Input {
private:
    double value;
    double weight;
public:
    Input(double value, double weight = -0.5 + ((double)rand()/RAND_MAX) * (0.5 + 0.5));

    double getValue();
    double getWeight();

    void setNewValue(double newValue);
    void setNewWeight(double newWeight);
};

#endif //NEURALNETWORK_INPUT_H
