//
// Created by pobi on 8/10/18.
//

#ifndef NEURALNETWORK_TEMPLATEFOREACHDELETEMETHOD_H
#define NEURALNETWORK_TEMPLATEFOREACHDELETEMETHOD_H

#include <vector>
#include <algorithm>

template<class T> void del(vector<T*> pointersVector)
{
    for_each(pointersVector.begin(), pointersVector.end(), [](T* ptr){delete ptr;});
}

#endif //NEURALNETWORK_TEMPLATEFOREACHDELETEMETHOD_H
