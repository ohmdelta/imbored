#define BOOST_TEST_MODULE Tests

#ifndef QUADRATIC_TEST_CPP
#define QUADRATIC_TEST_CPP

#include <boost/test/unit_test.hpp>

#include "polynomial.hpp"

BOOST_AUTO_TEST_SUITE(polynomialCubicSuite)

using namespace polynomial;

BOOST_AUTO_TEST_CASE(CubicSolutionStruct)
{
    CubicSolution q;

    BOOST_CHECK_EQUAL((int)q.num_solutions, 0);

    for (size_t i = 0; i < 3; i++)
    {
        BOOST_CHECK_EQUAL(q.sol[i], 0);
    }

    q.add_sol(1);
    BOOST_CHECK_EQUAL(q.num_solutions, 1);
    BOOST_CHECK_EQUAL(q.sol[0], 1);
}

BOOST_AUTO_TEST_CASE(CubicSolutionStructOverflowProtected)
{
    CubicSolution q;

    for (size_t i = 0; i < 3; i++)
    {
        BOOST_CHECK_EQUAL(q.num_solutions, i);

        q.add_sol(1);
        BOOST_CHECK_EQUAL(q.sol[i], 1);
    }

    BOOST_CHECK_EQUAL(q.num_solutions, 3);
    q.add_sol(1);
    BOOST_CHECK_EQUAL(q.num_solutions, 3);
}

BOOST_AUTO_TEST_CASE(CubicSolutionStructMinimum)
{
    CubicSolution q;

    for (int i = 0; i < 3; i++)
    {
        BOOST_CHECK_EQUAL(q.num_solutions, i);

        q.add_sol(i + 1);
        BOOST_CHECK_EQUAL(q.sol[i], i + 1);
    }

    BOOST_CHECK_EQUAL(q.num_solutions, 3);
    BOOST_CHECK_EQUAL(q.min(), 1);

    {
        CubicSolution q2;

        for (int i = 0; i < 3; i++)
        {
            q2.add_sol(-i);
        }

        BOOST_CHECK_EQUAL(q2.num_solutions, 3);
        for (int i = 0; i < 3; i++)
        {
            BOOST_CHECK_EQUAL(q2.sol[i], -i);
        }
        BOOST_CHECK_EQUAL(q2.min(), -2);
    }
}

BOOST_AUTO_TEST_CASE(SolveDepressedCubicEasy)
{
    // x ^ 3 - 1 = 0
    {
        auto sol = solve_depressed_cubic(0, -1);
        BOOST_CHECK_EQUAL(sol.num_solutions, 1);
        BOOST_CHECK_EQUAL(sol.sol[0], 1);
    }

    // x ^ 3  - 2x + 1 = 0
    // (x - 1)(x^2 + x - 1) = 0
    {
        auto sol = solve_depressed_cubic(-2, 1);
        BOOST_CHECK_EQUAL(sol.num_solutions, 3);
        for (auto &i : sol.sol)
        {
            double v = cube(i) - 2 * i + 1;
            BOOST_CHECK_CLOSE(v + 1, 1, 0.000001);
        }
    }
}

BOOST_AUTO_TEST_CASE(SolveCubicEasy)
{
    // (x - 1)(x^2  + 2x + 1) = 0
    // x^3  + x^2 - x - 1 = 0
    {
        auto sol = solve_cubic(1, 1, -1, -1);
        BOOST_CHECK_EQUAL(sol.num_solutions, 3);

        for (auto i : sol.sol)
        {
            double v = cube(i) + sq(i) - i - 1;
            BOOST_CHECK_CLOSE(v + 1, 1, 0.000001);
        }
    }
}

BOOST_AUTO_TEST_SUITE_END();

#endif