//
// Created by pobi on 11/18/18.
//

using namespace std;

#include <boost/test/unit_test.hpp>
#include <Layer.h>

BOOST_AUTO_TEST_SUITE(LayerTest)
    BOOST_AUTO_TEST_CASE(LayerIntsConstructor) {
        shared_ptr<Layer> layer = make_shared<Layer>(51, 31);

        //Check numbers of neurons
        BOOST_CHECK_EQUAL(layer->getNeurons().size(), 51);

        //Check numbers of inputs in every neuron
        //This is redundant test, because same test is in NeuronTest.cpp
        for(auto neuron: layer->getNeurons())
        {
            BOOST_CHECK_EQUAL(neuron->getInputs().size(), 31);
        }
    }
BOOST_AUTO_TEST_SUITE_END()