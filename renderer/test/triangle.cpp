#define BOOST_TEST_MODULE Tests

#include <boost/test/unit_test.hpp>
#include "renderer.hpp"

BOOST_AUTO_TEST_SUITE(TriangleSuite)

using namespace renderer;

BOOST_AUTO_TEST_CASE(TriangleIntersection)
{
    Triangle triangle(lin_alg::Coordinate(1, 0, 0), lin_alg::Coordinate(0, 1, 0));
    // triangle.set_origin(lin_alg::Coordinate(0, 0, 0));
    auto intersection = triangle.line_intersection(lin_alg::Coordinate(0, 0, 1), lin_alg::Coordinate(0.25, 0.25, -1));

    BOOST_CHECK(intersection.valid);

    BOOST_CHECK_EQUAL(intersection.coordinate.x, 0.25);
    BOOST_CHECK_EQUAL(intersection.coordinate.y, 0.25);
    BOOST_CHECK_EQUAL(intersection.coordinate.z, 0.0);

    BOOST_CHECK_EQUAL(intersection.coordinate.a, 1);

    auto intersection2 = triangle.line_intersection(lin_alg::Coordinate(0, 0, 1), lin_alg::Coordinate(1, 0.25, -1));
    BOOST_CHECK(!intersection2.valid);

}

BOOST_AUTO_TEST_SUITE_END();
