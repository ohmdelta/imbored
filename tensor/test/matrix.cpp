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

    BOOST_CHECK_EQUAL(C(0, 0), 3.0);
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

BOOST_AUTO_TEST_CASE(MatrixTranspose)
{
    Matrix<int> A(2, 3);

    for (size_t i = 0; i < 2; i++)
    {
        A(i, i) = 2;
    }

    A(1, 0) = 1;

    std::cout << A << std::endl;

    BOOST_CHECK_EQUAL(A(0, 0), 2.0);
    BOOST_CHECK_EQUAL(A(0, 1), 0.0);
    BOOST_CHECK_EQUAL(A(0, 2), 0.0);

    BOOST_CHECK_EQUAL(A(1, 0), 1.0);
    BOOST_CHECK_EQUAL(A(1, 1), 2.0);
    BOOST_CHECK_EQUAL(A(1, 2), 0.0);

    A.transpose_inplace();

    std::cout << A << std::endl;

    BOOST_CHECK_EQUAL(A.columns_, 2);
    BOOST_CHECK_EQUAL(A.rows_, 3);

    BOOST_CHECK_EQUAL(A(0, 0), 2.0);
    BOOST_CHECK_EQUAL(A(1, 0), 0.0);
    BOOST_CHECK_EQUAL(A(2, 0), 0.0);

    BOOST_CHECK_EQUAL(A(0, 1), 1.0);
    BOOST_CHECK_EQUAL(A(1, 1), 2.0);
    BOOST_CHECK_EQUAL(A(2, 1), 0.0);

    auto B = A.transpose();

    BOOST_CHECK(!B.transposed_);
    BOOST_CHECK_EQUAL(B(0, 0), 2.0);
    BOOST_CHECK_EQUAL(B(0, 1), 0.0);
    BOOST_CHECK_EQUAL(B(0, 2), 0.0);

    BOOST_CHECK_EQUAL(B(1, 0), 1.0);
    BOOST_CHECK_EQUAL(B(1, 1), 2.0);
    BOOST_CHECK_EQUAL(B(1, 2), 0.0);
};

BOOST_AUTO_TEST_CASE(MatrixTransposeMultiplication)
{
    Matrix<int> A(3, 2);

    for (size_t i = 0; i < 2; i++)
    {
        A(i, i) = 2;
    }

    A(2, 0) = 1;

    std::cout << A << std::endl;

    A.transpose_inplace();
    // std::cout << A.transposed_ << std::endl;
    // std::cout << A.rows_ << " , " << A.columns_ << std::endl;
    // std::cout << A << std::endl;
    BOOST_CHECK_EQUAL(A(0, 0), 2.0);
    BOOST_CHECK_EQUAL(A(0, 1), 0.0);
    BOOST_CHECK_EQUAL(A(0, 2), 1.0);

    BOOST_CHECK_EQUAL(A(1, 0), 0.0);
    BOOST_CHECK_EQUAL(A(1, 1), 2.0);
    BOOST_CHECK_EQUAL(A(1, 2), 0.0);

    Matrix<int> B(3, 1);
    B(0, 0) = 1;
    B(2, 0) = 1;

    auto C = A * B;
    std::cout << C << std::endl;
    BOOST_CHECK_EQUAL(C(0, 0), 3);
    BOOST_CHECK_EQUAL(C(1, 0), 0);
}

BOOST_AUTO_TEST_CASE(SlicedMatrixMultiplication)
{
    Matrix<int> A(3, 3);

    for (size_t i = 0; i < 2; i++)
    {
        A(i, i) = 2;
    }

    A(2, 2) = 1;

    std::cout << A << std::endl;
    SlicedMatrix<int> SA(std::make_shared<Matrix<int>>(A), 2, 2);

    std::cout << SA << std::endl;
    auto B = SA * SA;
    BOOST_CHECK_EQUAL(B.rows_, 2);
    BOOST_CHECK_EQUAL(B.columns_, 2);
    BOOST_CHECK_EQUAL(B(0, 0), 4);
    BOOST_CHECK_EQUAL(B(1, 1), 4);
    BOOST_CHECK_EQUAL(B(0, 1), 0);
    BOOST_CHECK_EQUAL(B(1, 0), 0);
}

BOOST_AUTO_TEST_CASE(SlicedSimpleStrassenMultiplication)
{
    Matrix<int> A(2, 2, 1);

    std::cout << A << std::endl;
    SlicedMatrix<int> SA(std::make_shared<Matrix<int>>(A), 2, 2);
    std::cout << SA << std::endl;

    auto B = SA * SA;
    BOOST_CHECK_EQUAL(B.rows_, 2);
    BOOST_CHECK_EQUAL(B.columns_, 2);
    BOOST_CHECK_EQUAL(B(0, 0), 2);
    BOOST_CHECK_EQUAL(B(1, 1), 2);
    BOOST_CHECK_EQUAL(B(0, 1), 2);
    BOOST_CHECK_EQUAL(B(1, 0), 2);

    auto C = SA.strassen_multiplication(SA);
    BOOST_CHECK_EQUAL(C.rows_, 2);
    BOOST_CHECK_EQUAL(C.columns_, 2);
    BOOST_CHECK_EQUAL(C(0, 0), 2);
    BOOST_CHECK_EQUAL(C(1, 1), 2);
    BOOST_CHECK_EQUAL(C(0, 1), 2);
    BOOST_CHECK_EQUAL(C(1, 0), 2);
}

BOOST_AUTO_TEST_CASE(SlicedToMatrix)
{
    Matrix<int> A(3, 3, 0);
    A(0, 0) = 2;
    A(0, 1) = 1;
    A(0, 2) = 5;
    A(1, 0) = 3;
    A(1, 1) = 2;
    A(1, 2) = 6;
    std::cout << A << std::endl;
    SlicedMatrix<int> SA(std::make_shared<Matrix<int>>(A), 2, 2);
    std::cout << SA << std::endl;
    Matrix<int> M = SA.toMatrix();
    std::cout << M << std::endl;

    BOOST_CHECK_EQUAL(M(0, 0), 2);
    BOOST_CHECK_EQUAL(M(0, 1), 1);
    BOOST_CHECK_EQUAL(M(1, 0), 3);
    BOOST_CHECK_EQUAL(M(1, 1), 2);

    SlicedMatrix<int> SA_2(std::make_shared<Matrix<int>>(A), 1, 3, 1, 3);
    Matrix<int> M_2 = SA_2.toMatrix();
    std::cout << M_2 << std::endl;

    BOOST_CHECK_EQUAL(M_2(0, 0), 2);
    BOOST_CHECK_EQUAL(M_2(0, 1), 6);
    BOOST_CHECK_EQUAL(M_2(1, 0), 0);
    BOOST_CHECK_EQUAL(M_2(1, 1), 0);

}

BOOST_AUTO_TEST_CASE(MatrixMatrixInsert)
{
    Matrix<int> A(2, 2, 1);

    std::cout << A << std::endl;
    SlicedMatrix<int> SA(std::make_shared<Matrix<int>>(A), 2, 2);
    std::cout << SA << std::endl;

    auto B = SA * SA;
    BOOST_CHECK_EQUAL(B.rows_, 2);
    BOOST_CHECK_EQUAL(B.columns_, 2);
    BOOST_CHECK_EQUAL(B(0, 0), 2);
    BOOST_CHECK_EQUAL(B(1, 1), 2);
    BOOST_CHECK_EQUAL(B(0, 1), 2);
    BOOST_CHECK_EQUAL(B(1, 0), 2);

    auto C = SA.strassen_multiplication(SA);
    BOOST_CHECK_EQUAL(C.rows_, 2);
    BOOST_CHECK_EQUAL(C.columns_, 2);
    BOOST_CHECK_EQUAL(C(0, 0), 2);
    BOOST_CHECK_EQUAL(C(1, 1), 2);
    BOOST_CHECK_EQUAL(C(0, 1), 2);
    BOOST_CHECK_EQUAL(C(1, 0), 2);
}

BOOST_AUTO_TEST_CASE(MatrixInsert)
{
    Matrix<int> A(3, 3, 1);

    std::cout << A << std::endl;
    Matrix<int> B(2, 2, 2);
    A.insert_matrix(B, 2, 2);

    std::cout << A << std::endl;
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (i == 2 && j == 2)
            {
                BOOST_CHECK_EQUAL(A(i, j), 2);
            }
            else
                BOOST_CHECK_EQUAL(A(i, j), 1);
        }
    }
}

BOOST_AUTO_TEST_CASE(StrassenMultiplicationSimpleSmall)
{
    Matrix<int> A(2, 2, 1);
    Matrix<int> B(2, 2, 0);
    for (size_t i = 0; i < 2; i++)
    {
        B(i, i) = 2;
    }

    std::cout << A * B << std::endl;
    auto C = A.strassen_multiplication(B);
    std::cout << C << std::endl;

    BOOST_CHECK_EQUAL(C.rows_, 2);
    BOOST_CHECK_EQUAL(C.columns_, 2);

    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            BOOST_CHECK_EQUAL(C(i, j), 2);
        }
    }

}

BOOST_AUTO_TEST_CASE(StrassenMultiplicationSmall)
{
    Matrix<int> A(4, 4, 1);
    Matrix<int> B(4, 4, 0);
    for (size_t i = 0; i < 4; i++)
    {
        B(i, i) = 2;
    }

    auto a = SlicedMatrix(std::make_shared<Matrix<int>>(A));
    auto b = SlicedMatrix(std::make_shared<Matrix<int>>(B));
    std::cout << a << std::endl << b << std::endl;
    // std::cout << A * B << std::endl;
    auto C = a.strassen_multiplication(b);
    std::cout << C << std::endl;

    BOOST_CHECK_EQUAL(C.rows_, 4);
    BOOST_CHECK_EQUAL(C.columns_, 4);

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            BOOST_CHECK_EQUAL(C(i, j), 2);
        }
    }

}

BOOST_AUTO_TEST_CASE(StrassenMultiplicationMedium)
{
    Matrix<int> A(32, 32, 0);
    Matrix<int> B(32, 32, 0);
    for (size_t i = 0; i < A.len_; i++)
    {
        A.matrix_[i] = i + 1;
        B.matrix_[i] = A.len_ - i;
    }

    auto C = A * B;
    BOOST_CHECK_EQUAL(C.rows_, 32);
    BOOST_CHECK_EQUAL(C.columns_, 32);


    auto D = A * B;
    BOOST_CHECK_EQUAL(D.rows_, 32);
    BOOST_CHECK_EQUAL(D.columns_, 32);
    for (size_t i = 0; i < C.len_; i++)
    {
        BOOST_CHECK_EQUAL(C.matrix_[i], D.matrix_[i]);
    }

}

BOOST_AUTO_TEST_CASE(StrassenMultiplicationLarge)
{
    Matrix<int> A(512, 512, 0);
    Matrix<int> B(512, 512, 0);
    for (size_t i = 0; i < A.len_; i++)
    {
        A.matrix_[i] = i + 1;
        B.matrix_[i] = A.len_ - i;
    }

    auto C = A * B;
    BOOST_CHECK_EQUAL(C.rows_, 512);
    BOOST_CHECK_EQUAL(C.columns_, 512);


    auto D = A * B;
    BOOST_CHECK_EQUAL(D.rows_, 512);
    BOOST_CHECK_EQUAL(D.columns_, 512);
    for (size_t i = 0; i < C.len_; i++)
    {
        BOOST_CHECK_EQUAL(C.matrix_[i], D.matrix_[i]);
    }

}

BOOST_AUTO_TEST_SUITE_END();
