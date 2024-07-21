#define BOOST_TEST_MAIN
#if !defined(WIN32)
    #define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>

#include "../lin_alg/coordinate.hpp"

using namespace lin_alg;

BOOST_AUTO_TEST_CASE(la)
{
    Coordinate coord1(1, 2, 3);
    Coordinate coord2(2, 3, 4);

    auto coord3 = coord1 + coord2;
    Coordinate coord4(3, 5, 7);
    BOOST_CHECK(coord3 == coord4);
}


BOOST_AUTO_TEST_CASE(multiplication)
{
    auto coord1 = Coordinate(1, 2, 3);
    auto coord2 = Coordinate(2, 3, 4);

    auto coord3 = coord1 * coord2;
    auto coord4 = Coordinate(2, 6, 12);
    BOOST_CHECK(coord3 == coord4);
}

BOOST_AUTO_TEST_CASE(subtraction)
{
    auto coord1 = Coordinate(1, 2, 3);
    auto coord2 = Coordinate(2, 3, 4);

    auto coord3 = coord2 - coord1;
    auto coord4 = Coordinate(1, 1, 1);
    BOOST_CHECK(coord3 == coord4);
}

BOOST_AUTO_TEST_CASE(lessthan)
{
    auto coord1 = Coordinate(1, 2, 3);
    auto coord2 = Coordinate(2, 3, 4);

    BOOST_CHECK(coord1 < coord2);
}


BOOST_AUTO_TEST_CASE(leq)
{
    Coordinate coord1(1, 3, 4);
    Coordinate coord2(2, 3, 4);

    BOOST_CHECK(coord1 <= coord2);
    Coordinate coord3(3, 3, 4);
    Coordinate coord4(2, 3, 4);

    BOOST_CHECK(!(coord3 <= coord4));
}
