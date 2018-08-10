//
// Created by pobi on 8/1/18.
//

#include <boost/test/unit_test.hpp>
#include <Neuron.h>
using namespace std;

BOOST_AUTO_TEST_SUITE(NeuronTest)
    BOOST_AUTO_TEST_CASE(OneElementConstructor)
    {
        Neuron* neuron = new Neuron(3);


        BOOST_CHECK_EQUAL(neuron->getInput(0), nullptr);
        BOOST_CHECK_EQUAL(neuron->getInput(1), nullptr);

        delete neuron;
    }

    BOOST_AUTO_TEST_CASE(GetBiasTest)
    {
        Neuron* neuron = new Neuron(new Input(5), 3);

        BOOST_CHECK_EQUAL(neuron->getBias()->getValue(), 5);
        BOOST_CHECK_EQUAL(neuron->getBias()->getWeight(), 1.0);


        delete neuron;
    }


BOOST_AUTO_TEST_SUITE_END()