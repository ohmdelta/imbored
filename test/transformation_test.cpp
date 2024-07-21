#define BOOST_TEST_MAIN
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>

#include "../lin_alg/lin_alg.hpp"

using namespace lin_alg;

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