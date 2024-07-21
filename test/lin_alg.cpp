#define BOOST_TEST_MAIN
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>

#include "../lin_alg/coordinate.hpp"

using namespace lin_alg;

BOOST_AUTO_TEST_CASE(addition)
{
    Coordinate coord1(1, 2, 3);
    Coordinate coord2(2, 3, 4);

    auto coord3 = coord1 + coord2;

    BOOST_CHECK(coord3 == Coordinate(3, 5, 7));
}

BOOST_AUTO_TEST_CASE(multiplication)
{
    Coordinate coord1(1, 2, 3);
    Coordinate coord2(2, 3, 4);

    auto coord3 = coord1 * coord2;
    BOOST_CHECK(coord3 == Coordinate(2, 6, 12));
}

BOOST_AUTO_TEST_CASE(subtraction)
{
    Coordinate coord1(1, 2, 3);
    Coordinate coord2(2, 3, 4);

    auto coord3 = coord2 - coord1;
    BOOST_CHECK(coord3 == Coordinate(1, 1, 1));
}

BOOST_AUTO_TEST_CASE(lessthan)
{
    Coordinate coord1(1, 2, 3);
    Coordinate coord2(2, 3, 4);

    BOOST_CHECK(coord1 < coord2);
}

BOOST_AUTO_TEST_CASE(leq)
{
    Coordinate coord1(1, 3, 4);
    Coordinate coord2(2, 3, 4);

    BOOST_CHECK(coord1 <= coord2);
    BOOST_CHECK(!(coord1 < coord2));

    Coordinate coord3(3, 3, 4);
    Coordinate coord4(2, 3, 4);

    BOOST_CHECK(!(coord3 <= coord4));
}

BOOST_AUTO_TEST_CASE(geq)
{
    Coordinate coord1(1, 3, 4);
    Coordinate coord2(2, 3, 4);

    BOOST_CHECK(coord2 >= coord1);
    BOOST_CHECK(!(coord2 > coord1));

    Coordinate coord3(3, 3, 4);
    Coordinate coord4(2, 3, 4);

    BOOST_CHECK(!(coord4 >= coord3));
}

BOOST_AUTO_TEST_CASE(peq)
{
    Coordinate coord1(1, 3, 4);
    Coordinate coord2(2, 3, 4);

    coord1 += coord2;

    BOOST_CHECK(coord1 == Coordinate(3, 6, 8));

    coord1 += 10;
    BOOST_CHECK(coord1 == Coordinate(13, 16, 18));
}

BOOST_AUTO_TEST_CASE(neq)
{
    Coordinate coord1(1, 3, 4);
    Coordinate coord2(2, 3, 4);

    coord1 -= coord2;

    BOOST_CHECK(coord1 == Coordinate(-1, 0, 0));

    coord1 -= 10;
    BOOST_CHECK(coord1 == Coordinate(-11, -10, -10));
}

BOOST_AUTO_TEST_CASE(meq)
{
    Coordinate coord1(1, 3, 4);
    Coordinate coord2(2, 3, 4);

    coord1 *= coord2;

    BOOST_CHECK(coord1 == Coordinate(2, 9, 16));

    coord2 *= 2;

    BOOST_CHECK(coord2 == Coordinate(4, 6, 8));
}

BOOST_AUTO_TEST_CASE(deq)
{
    Coordinate coord1(1, 3, 4);
    Coordinate coord2(2, 3, 4);

    coord2 /= coord1;

    BOOST_CHECK(coord2 == Coordinate(2, 1, 1));

    coord2 /= 2;
    auto expected = Coordinate(1, 0.5, 0.5);
    for (size_t i = 0; i < 3; i++)
    {
        BOOST_CHECK_EQUAL(coord2[i], expected[i]);
    }

    BOOST_CHECK_THROW(coord2 /= 0, std::runtime_error);
}
