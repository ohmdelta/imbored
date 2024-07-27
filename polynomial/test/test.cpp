#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Tests
#endif

#include <boost/test/unit_test.hpp>
#include "polynomial.hpp"

BOOST_AUTO_TEST_SUITE(polynomial)

using namespace polynomial;

BOOST_AUTO_TEST_CASE(QuarticSolutionStruct)
{
    QuarticSolution q;

    BOOST_CHECK_EQUAL(q.num_solutions, 0);

    for (size_t i = 0; i < 4; i++)
    {
        BOOST_CHECK_EQUAL(q.sol[i], 0);
    }

    q.add_sol(1);
    BOOST_CHECK_EQUAL(q.num_solutions, 1);
    BOOST_CHECK_EQUAL(q.sol[0], 1);
}

BOOST_AUTO_TEST_CASE(QuarticSolutionStructOverflowProtected)
{
    QuarticSolution q;

    for (size_t i = 0; i < 4; i++)
    {
        BOOST_CHECK_EQUAL(q.num_solutions, i);

        q.add_sol(1);
        BOOST_CHECK_EQUAL(q.sol[i], 1);
    }

    BOOST_CHECK_EQUAL(q.num_solutions, 4);
    q.add_sol(1);
    BOOST_CHECK_EQUAL(q.num_solutions, 4);
}

BOOST_AUTO_TEST_CASE(QuarticSolutionStructMinimum)
{
    QuarticSolution q;

    for (int i = 0; i < 4; i++)
    {
        BOOST_CHECK_EQUAL(q.num_solutions, i);

        q.add_sol(i + 1);
        BOOST_CHECK_EQUAL(q.sol[i], i + 1);
    }

    BOOST_CHECK_EQUAL(q.num_solutions, 4);
    BOOST_CHECK_EQUAL(q.min(), 1);

    {
        QuarticSolution q2;

        for (int i = 0; i < 4; i++)
        {
            q2.add_sol(-i);
        }

        BOOST_CHECK_EQUAL(q2.num_solutions, 4);
        for (int i = 0; i < 4; i++)
        {
            BOOST_CHECK_EQUAL(q2.sol[i],-i);
        }
        BOOST_CHECK_EQUAL(q2.min(), -3);
    }
}

BOOST_AUTO_TEST_SUITE_END();
