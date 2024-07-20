#define BOOST_TEST_MAIN
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>
#include "../lin_alg/coordinate.hpp"

using namespace lin_alg;

BOOST_AUTO_TEST_CASE(la)
{
    auto coord1 = Coordinate(1, 2, 3);
    auto coord2 = Coordinate(2, 3, 4);

    auto coord3 = coord1 + coord2;
    BOOST_CHECK(coord3 == Coordinate(3, 5, 7));
}


BOOST_AUTO_TEST_CASE(multiplication)
{
    auto coord1 = Coordinate(1, 2, 3);
    auto coord2 = Coordinate(2, 3, 4);

    auto coord3 = coord1 * coord2;
    BOOST_CHECK(coord3 == Coordinate(2, 6, 12));
}