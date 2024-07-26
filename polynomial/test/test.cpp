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
    
}

BOOST_AUTO_TEST_SUITE_END();
