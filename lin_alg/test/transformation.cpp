#define BOOST_TEST_MODULE Tests

#include <boost/test/unit_test.hpp>

#include "lin_alg.hpp"

using namespace lin_alg;

BOOST_AUTO_TEST_SUITE(Transformation)

BOOST_AUTO_TEST_CASE(TransformationAddition)
{
    TransformationMatrix a = Identity();
    TransformationMatrix b = Ones();
    b *= 2;
    std::cout << b << std::endl;
    TransformationMatrix c = a + b;

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if (i == j)
            {
                BOOST_CHECK_EQUAL(c(i, j), 3);
            }
            else
            {
                BOOST_CHECK_EQUAL(c(i, j), 2);
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(TransformationMultiplication)
{
    TransformationMatrix a = Identity();
    TransformationMatrix b = Ones();
    b *= 2;
    TransformationMatrix c = a * b;

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            BOOST_CHECK_EQUAL(c(i, j), 2);
        }
    }

    for (size_t i = 0; i < 4; i++)
    {
        a(i, i) = i;
    }

    TransformationMatrix d = a * a;
    for (size_t i = 0; i < 4; i++)
    {
        BOOST_CHECK_EQUAL(d(i, i), i * i);
    }
}

BOOST_AUTO_TEST_CASE(transformation_equality)
{
    TransformationMatrix matrix;
    matrix(1, 3) = 1;
    auto matrix_2 = matrix;

    BOOST_CHECK(matrix == matrix_2);
}

BOOST_AUTO_TEST_CASE(transpose)
{
    TransformationMatrix matrix;
    matrix(1, 3) = 1;
    auto matrix_2 = matrix;

    BOOST_CHECK(matrix == matrix_2);

    matrix_2.transpose();
    BOOST_CHECK(matrix != matrix_2);
    BOOST_CHECK(matrix_2(3, 1) == 1);

    matrix_2.transpose();

    BOOST_CHECK(matrix == matrix_2);
}

BOOST_AUTO_TEST_CASE(identity)
{
    TransformationMatrix matrix = Identity();
    Vector coord(1, 2, 3);

    auto coord2 = matrix * coord;
    BOOST_CHECK(coord == coord2);
}

BOOST_AUTO_TEST_CASE(multiplication)
{
    TransformationMatrix matrix = Identity();
    Vector coord(1, 2, 3);

    auto coord2 = matrix * coord;
    BOOST_CHECK(coord == coord2);
    matrix(0, 3) = 1;

    BOOST_CHECK(Vector(2, 2, 3, 1) == matrix * coord);
}

BOOST_AUTO_TEST_SUITE_END();
