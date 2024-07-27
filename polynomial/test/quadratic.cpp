#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Tests
#endif

#ifndef QUADRATIC_TEST_CPP
#define QUADRATIC_TEST_CPP

#include <boost/test/unit_test.hpp>

#include "polynomial.hpp"

BOOST_AUTO_TEST_SUITE(polynomialQuadraticSuite)

using namespace polynomial;

BOOST_AUTO_TEST_CASE(QuadraticSolutionStruct)
{
    QuadraticSolution q;

    BOOST_CHECK_EQUAL((int) q.num_solutions, 0);

    for (size_t i = 0; i < 2; i++)
    {
        BOOST_CHECK_EQUAL(q.sol[i], 0);
    }

    q.add_sol(1);
    BOOST_CHECK_EQUAL(q.num_solutions, 1);
    BOOST_CHECK_EQUAL(q.sol[0], 1);
}

BOOST_AUTO_TEST_CASE(QuadraticSolutionStructOverflowProtected)
{
    QuadraticSolution q;

    for (size_t i = 0; i < 2; i++)
    {
        BOOST_CHECK_EQUAL(q.num_solutions, i);

        q.add_sol(1);
        BOOST_CHECK_EQUAL(q.sol[i], 1);
    }

    BOOST_CHECK_EQUAL(q.num_solutions, 2);
    q.add_sol(1);
    BOOST_CHECK_EQUAL(q.num_solutions, 2);
}

BOOST_AUTO_TEST_CASE(QuadraticSolutionStructMinimum)
{
    QuadraticSolution q;

    for (int i = 0; i < 2; i++)
    {
        BOOST_CHECK_EQUAL(q.num_solutions, i);

        q.add_sol(i + 1);
        BOOST_CHECK_EQUAL(q.sol[i], i + 1);
    }

    BOOST_CHECK_EQUAL(q.num_solutions, 2);
    BOOST_CHECK_EQUAL(q.min(), 1);

    {
        QuadraticSolution q2;

        for (int i = 0; i < 2; i++)
        {
            q2.add_sol(-i);
        }

        BOOST_CHECK_EQUAL(q2.num_solutions, 2);
        for (int i = 0; i < 2; i++)
        {
            BOOST_CHECK_EQUAL(q2.sol[i], -i);
        }
        BOOST_CHECK_EQUAL(q2.min(), -1);
    }
}

BOOST_AUTO_TEST_CASE(QuadraticSolutionEasy)
{
    // x ^ 2 - 1 = 0
    {
        auto sol = solve_quadratic(1, 0, -1);

        BOOST_CHECK_EQUAL(sol.num_solutions, 2);
        BOOST_CHECK_EQUAL(sol.sol[0], -1);
        BOOST_CHECK_EQUAL(sol.sol[1], 1);
    }

    // x ^ 2 - x = 0
    {
        auto sol = solve_quadratic(1, 1, 0);

        BOOST_CHECK_EQUAL(sol.num_solutions, 2);
        BOOST_CHECK_EQUAL(sol.sol[0], -1);
        BOOST_CHECK_EQUAL(sol.sol[1], 0);
    }


    // x ^ 2 + 2x + 1 = 0
    {
        auto sol = solve_quadratic(1, 2, 1);

        BOOST_CHECK_EQUAL(sol.num_solutions, 1);
        BOOST_CHECK_EQUAL(sol.sol[0], -1);
    }

    // x ^ 2 + 2x + 5 = 0
    {
        auto sol = solve_quadratic(1, 2, 5);

        BOOST_CHECK_EQUAL(sol.num_solutions, 0);
    }
}

BOOST_AUTO_TEST_SUITE_END();

#endif