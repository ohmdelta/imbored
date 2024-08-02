#define BOOST_TEST_MODULE Tests

#include <boost/test/unit_test.hpp>
#include "renderer.hpp"

BOOST_AUTO_TEST_SUITE(PlaneSuite)

using namespace renderer;

BOOST_AUTO_TEST_CASE(PlaneIntersection)
{
    Plane plane(lin_alg::Origin(), lin_alg::Coordinate(0, 0, 1));

    auto intersection = plane.line_intersection(lin_alg::Coordinate(0, 0, 1), lin_alg::Coordinate(0, 0, -1));
    for (size_t i = 0; i < 3; i++)
    {
        BOOST_CHECK_EQUAL(intersection.coordinate[i], 0);
    }

    BOOST_CHECK_EQUAL(intersection.coordinate.a, 1);
}

BOOST_AUTO_TEST_SUITE_END();
