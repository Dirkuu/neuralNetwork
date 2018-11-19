//
// Created by pobi on 11/18/18.
//

using namespace std;

#include <boost/test/unit_test.hpp>
#include <ctime>
#include <Layer.h>

BOOST_AUTO_TEST_SUITE(LayerTest)
    BOOST_AUTO_TEST_CASE(LayerVectorConstructor) {
        srand(time(0));

        vector<shared_ptr<Input>> input1;
        input1.emplace_back(make_shared<Input>(1));
        vector<shared_ptr<Input>> input2;
        input2.emplace_back(make_shared<Input>(0));
        vector<shared_ptr<Input>> input3;
        input3.emplace_back(make_shared<Input>(0));
        vector<shared_ptr<Input>> input4;
        input4.emplace_back(make_shared<Input>(0));

        vector<shared_ptr<Neuron>> neurons;
        neurons.emplace_back(make_shared<Neuron>(input1));
        neurons.emplace_back(make_shared<Neuron>(input2));
        neurons.emplace_back(make_shared<Neuron>(input3));
        neurons.emplace_back(make_shared<Neuron>(input4));

        shared_ptr<Layer> layer = make_shared<Layer>(neurons);

        //Check numbers of neurons
        BOOST_CHECK_EQUAL(layer->getNeurons().size(), 4);

        //Check values of inputs in neurons
        BOOST_CHECK_EQUAL(layer->getNeurons().at(0)->getInputs().at(0)->getValue(), 1);
        BOOST_CHECK_EQUAL(layer->getNeurons().at(1)->getInputs().at(0)->getValue(), 0);
        BOOST_CHECK_EQUAL(layer->getNeurons().at(2)->getInputs().at(0)->getValue(), 0);
        BOOST_CHECK_EQUAL(layer->getNeurons().at(3)->getInputs().at(0)->getValue(), 0);
    }

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