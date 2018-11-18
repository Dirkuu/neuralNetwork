//
// Created by pobi on 8/1/18.
//

using namespace std;

#include <boost/test/unit_test.hpp>
#include <Neuron.h>

BOOST_AUTO_TEST_SUITE(NeuronTest)
    BOOST_AUTO_TEST_CASE(NeuronConstructorTestWithoutBias)
    {
        vector<shared_ptr<Input>> inputs;
        inputs.emplace_back(make_shared<Input>(58));
        inputs.emplace_back(make_shared<Input>(58));
        inputs.emplace_back(make_shared<Input>(58));
        inputs.emplace_back(make_shared<Input>(58));

        shared_ptr<Neuron> neuron = make_shared<Neuron>(inputs);

        //normal inputs test
        for (auto input : neuron->getInputs())
        {
            BOOST_CHECK_EQUAL(input->getValue(), 58);
        }
    }

    BOOST_AUTO_TEST_CASE(NeuronConstructorTestWithBias)
    {
        vector<shared_ptr<Input>> inputs;
        inputs.emplace_back(make_shared<Input>(58));
        inputs.emplace_back(make_shared<Input>(58));
        inputs.emplace_back(make_shared<Input>(58));
        inputs.emplace_back(make_shared<Input>(58));

        shared_ptr<Neuron> neuron = make_shared<Neuron>(inputs, make_shared<Input>(54));

        //normal inputs test
        for (auto input : neuron->getInputs())
        {
            BOOST_CHECK_EQUAL(input->getValue(), 58);
        }

        //bias test
        BOOST_CHECK_EQUAL(neuron->getBias()->getValue(), 54);
    }

    BOOST_AUTO_TEST_CASE(NeuronSumMethodTestWithoutBias)
    {
        vector<shared_ptr<Input>> inputs;
        inputs.emplace_back(make_shared<Input>(1, 0.33));
        inputs.emplace_back(make_shared<Input>(0, 1));
        inputs.emplace_back(make_shared<Input>(8, 0.05));
        inputs.emplace_back(make_shared<Input>(5, -0.4));

        shared_ptr<Neuron> neuron = make_shared<Neuron>(inputs);

        //BOOST_CHECK_EQUAL(neuron->)
    }
BOOST_AUTO_TEST_SUITE_END()