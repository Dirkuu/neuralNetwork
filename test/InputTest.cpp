//
// Created by Wojtek on 2018-07-19.
//


#include <boost/test/unit_test.hpp>
#include "Input.h"
using namespace std;

BOOST_AUTO_TEST_SUITE(InputTest)
    BOOST_AUTO_TEST_CASE(DefaultWeightTest)
    {
        Input* testInput = new Input(5.3);

        BOOST_CHECK_EQUAL(testInput->getValue(), 5.3);

        bool defaultWeightInterval;
        if (testInput->getWeight() >= -0.5 && testInput->getWeight() <= 0.5)            defaultWeightInterval = true;
        else                                                                            defaultWeightInterval = false;

        BOOST_CHECK_EQUAL(defaultWeightInterval, true);

        delete testInput;
    }

    BOOST_AUTO_TEST_CASE(AllConstructorArgumentsTest)
    {
        Input* testInput = new Input(5.3, 1.2);

        BOOST_CHECK_EQUAL(testInput->getValue(), 5.3000);
        BOOST_CHECK_EQUAL(testInput->getWeight(), 1.20);

        delete testInput;
    }
BOOST_AUTO_TEST_SUITE_END()