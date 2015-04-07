#include "stdafx.h"

#include <boost/test/unit_test.hpp>
#include <iostream>


#define BOOST_TEST_MODULE RecorderGMMTest
BOOST_AUTO_TEST_CASE( my_test )
{
    RecorderGMM test_object("movement13.avi");

    BOOST_CHECK( 1 == 1 );

}
