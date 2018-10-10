//
// Created by pobi on 8/1/18.
//

using namespace std;

#include <boost/test/unit_test.hpp>
#include <Neuron.h>

BOOST_AUTO_TEST_SUITE(NeuronTest)
    BOOST_AUTO_TEST_CASE(OneDoubleElementConstructor)
    {
        Neuron* neuron = new Neuron(3);


        BOOST_CHECK_EQUAL(neuron->getInput(0).getValue(), 3);

        bool defaultWeightInterval;
        if (neuron->getInput(0).getWeight() >= -0.5 && neuron->getInput(0).getWeight() <= 0.5)              defaultWeightInterval = true;
        else                                                                                                defaultWeightInterval = false;

        BOOST_CHECK_EQUAL(defaultWeightInterval, true);

        delete neuron;
    }

    BOOST_AUTO_TEST_CASE(GetBiasTest)
    {
        vector<Input> inputs;
        inputs.emplace_back(5);

        Neuron* neuron = new Neuron(inputs);


        bool nullptrBool;
        if (neuron->getBias() == nullptr)                   nullptrBool = true;
        else                                                nullptrBool = false;

        BOOST_CHECK_EQUAL(nullptrBool, true);


        delete neuron;
    }

    BOOST_AUTO_TEST_CASE(DAFUQdeleteThisTestToKnow)
    {
        BOOST_CHECK_EQUAL(1, 1);
    }


BOOST_AUTO_TEST_SUITE_END()