#define BOOST_TEST_MODULE Tests

#include <boost/test/unit_test.hpp>

#include "lin_alg.hpp"

using namespace lin_alg;

BOOST_AUTO_TEST_SUITE(CoordinateSuite)

BOOST_AUTO_TEST_CASE(CoordinateCrossProduct)
{
    Coordinate coordinate1(1, 0, 0);
    Coordinate coordinate2(0, 1, 0);
    std::cout << coordinate1 << " , " << coordinate2 << std::endl;

    Coordinate result = coordinate1.cross(coordinate2);
    std::cout << result << std::endl;
    BOOST_CHECK_CLOSE_FRACTION(result.x, 0, 0.00001);
    BOOST_CHECK_CLOSE_FRACTION(result.y, 0, 0.00001);
    BOOST_CHECK_CLOSE_FRACTION(result.z, 1, 0.00001);

    BOOST_CHECK_CLOSE_FRACTION(result.a, 1, 0.00001);
    
}

BOOST_AUTO_TEST_SUITE_END();
