#define BOOST_TEST_MODULE Tests

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestSuite)

BOOST_AUTO_TEST_CASE(Test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(Test2)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END();
