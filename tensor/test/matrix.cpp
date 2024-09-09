#define BOOST_TEST_MODULE Tests

#include <boost/test/unit_test.hpp>

#include "matrix.hpp"

BOOST_AUTO_TEST_SUITE(MatrixTestSuite)

using namespace tensor;

BOOST_AUTO_TEST_CASE(MatrixCreation)
{
    Matrix<float> matrix(10, 10);
}

BOOST_AUTO_TEST_CASE(MatrixAccess)
{
    Matrix<float> matrix(10, 10);
    matrix(0, 0) = 10;
    BOOST_CHECK_EQUAL(matrix(0, 0), 10);
    BOOST_CHECK_THROW(matrix(10, 0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(MatrixMultiplication)
{
    Matrix<int> A(3, 3);
    Matrix<float> B(3, 3);
    B(0, 0) = 1.0;
    B(0, 2) = 2.0;

    BOOST_CHECK_EQUAL(B(0, 0), 1.0);
    for (size_t i = 0; i < 3; i++)
    {
        A(i, i) = 2;
    }

    auto C = A * B;

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    BOOST_CHECK_EQUAL(C(0, 0), 2.0);
                    continue;
                }
                else if (j == 2)
                {
                    BOOST_CHECK_EQUAL(C(0, 2), 4.0);
                    continue;
                }
            }
            BOOST_CHECK_EQUAL(C(i, j), 0.0);
        }
    }

    A *= 3.0;

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (i == j)
                BOOST_CHECK_EQUAL(A(i, j), 6.0);
            else
                BOOST_CHECK_EQUAL(A(i, j), 0.0);
        }
    }
    
}

BOOST_AUTO_TEST_CASE(MatrixAddition)
{
    Matrix<int> A(3, 3);
    Matrix<float> B(3, 3);
    B(0, 0) = 1.0;
    B(0, 2) = 2.0;

    BOOST_CHECK_EQUAL(B(0, 0), 1.0);
    for (size_t i = 0; i < 3; i++)
    {
        A(i, i) = 2;
    }

    // std::cout << (A * B) << std::endl;
    auto C = A + B;

    BOOST_CHECK_EQUAL(C(0, 0), 4.0);
    BOOST_CHECK_EQUAL(C(0, 1), 0.0);
    BOOST_CHECK_EQUAL(C(0, 2), 2.0);
 
    BOOST_CHECK_EQUAL(C(1, 0), 0.0);
    BOOST_CHECK_EQUAL(C(1, 1), 2.0);
    BOOST_CHECK_EQUAL(C(1, 2), 0.0);

    BOOST_CHECK_EQUAL(C(2, 0), 0.0);
    BOOST_CHECK_EQUAL(C(2, 1), 0.0);
    BOOST_CHECK_EQUAL(C(2, 2), 2.0);

    A += 3.0;

    BOOST_CHECK_EQUAL(A(0, 0), 5.0);
    BOOST_CHECK_EQUAL(A(0, 1), 3.0);
    BOOST_CHECK_EQUAL(A(0, 2), 3.0);
 
    BOOST_CHECK_EQUAL(A(1, 0), 3.0);
    BOOST_CHECK_EQUAL(A(1, 1), 5.0);
    BOOST_CHECK_EQUAL(A(1, 2), 3.0);

    BOOST_CHECK_EQUAL(A(2, 0), 3.0);
    BOOST_CHECK_EQUAL(A(2, 1), 3.0);
    BOOST_CHECK_EQUAL(A(2, 2), 5.0);

};

BOOST_AUTO_TEST_SUITE_END();
