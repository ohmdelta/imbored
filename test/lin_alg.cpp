#define BOOST_TEST_MAIN
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>

#include "../lin_alg/coordinate.hpp"

using namespace lin_alg;

BOOST_AUTO_TEST_CASE(dotproduct)
{
    Vector coord1(1, 2, 3);
    Vector coord2(2, 3, 4);

    auto dot1 = coord1.dot(coord2);

    BOOST_CHECK(dot1 == (2 + 6 + 12 + 1));
    auto dot2 = coord2.dot(coord1);
    BOOST_CHECK(dot1 == dot2);
}

BOOST_AUTO_TEST_CASE(sum)
{
    Vector coord1(1, 2, 3);

    auto sum = coord1.sum();

    BOOST_CHECK(sum == 7);
}


BOOST_AUTO_TEST_CASE(addition)
{
    Vector coord1(1, 2, 3);
    Vector coord2(2, 3, 4);

    auto coord3 = coord1 + coord2;

    BOOST_CHECK(coord3 == Vector(3, 5, 7));
}

BOOST_AUTO_TEST_CASE(multiplication)
{
    Vector coord1(1, 2, 3);
    Vector coord2(2, 3, 4);

    auto coord3 = coord1 * coord2;
    BOOST_CHECK(coord3 == Vector(2, 6, 12));
}

BOOST_AUTO_TEST_CASE(subtraction)
{
    Vector coord1(1, 2, 3);
    Vector coord2(2, 3, 4);

    auto coord3 = coord2 - coord1;
    BOOST_CHECK(coord3 == Vector(1, 1, 1));
}

BOOST_AUTO_TEST_CASE(lessthan)
{
    Vector coord1(1, 2, 3);
    Vector coord2(2, 3, 4);

    BOOST_CHECK(coord1 < coord2);
}

BOOST_AUTO_TEST_CASE(leq)
{
    Vector coord1(1, 3, 4);
    Vector coord2(2, 3, 4);

    BOOST_CHECK(coord1 <= coord2);
    BOOST_CHECK(!(coord1 < coord2));

    Vector coord3(3, 3, 4);
    Vector coord4(2, 3, 4);

    BOOST_CHECK(!(coord3 <= coord4));
}

BOOST_AUTO_TEST_CASE(geq)
{
    Vector coord1(1, 3, 4);
    Vector coord2(2, 3, 4);

    BOOST_CHECK(coord2 >= coord1);
    BOOST_CHECK(!(coord2 > coord1));

    Vector coord3(3, 3, 4);
    Vector coord4(2, 3, 4);

    BOOST_CHECK(!(coord4 >= coord3));
}

BOOST_AUTO_TEST_CASE(peq)
{
    Vector coord1(1, 3, 4);
    Vector coord2(2, 3, 4);

    coord1 += coord2;

    BOOST_CHECK(coord1 == Vector(3, 6, 8));

    coord1 += 10;
    BOOST_CHECK(coord1 == Vector(13, 16, 18));
}

BOOST_AUTO_TEST_CASE(neq)
{
    Vector coord1(1, 3, 4);
    Vector coord2(2, 3, 4);

    coord1 -= coord2;

    BOOST_CHECK(coord1 == Vector(-1, 0, 0));

    coord1 -= 10;
    BOOST_CHECK(coord1 == Vector(-11, -10, -10));
}

BOOST_AUTO_TEST_CASE(meq)
{
    Vector coord1(1, 3, 4);
    Vector coord2(2, 3, 4);

    coord1 *= coord2;

    BOOST_CHECK(coord1 == Vector(2, 9, 16));

    coord2 *= 2;

    BOOST_CHECK(coord2 == Vector(4, 6, 8));
}

BOOST_AUTO_TEST_CASE(deq)
{
    Vector coord1(1, 3, 4);
    Vector coord2(2, 3, 4);

    coord2 /= coord1;

    BOOST_CHECK(coord2 == Vector(2, 1, 1));

    coord2 /= 2;
    auto expected = Vector(1, 0.5, 0.5);
    for (size_t i = 0; i < 3; i++)
    {
        BOOST_CHECK_EQUAL(coord2[i], expected[i]);
    }

    BOOST_CHECK_THROW(coord2 /= 0, std::runtime_error);
}
