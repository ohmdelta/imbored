#define BOOST_TEST_MODULE Tests

#include <boost/test/unit_test.hpp>
#include "renderer.hpp"

BOOST_AUTO_TEST_SUITE(TorusSuite)

using namespace renderer;

BOOST_AUTO_TEST_CASE(TorusIntersection)
{
    Torus torus(10, 20, lin_alg::Coordinate(50, 0, 0));
    auto intersection = torus.line_intersection(lin_alg::Origin(), lin_alg::Coordinate(1, 0, 0));

    BOOST_CHECK(intersection.valid);
    BOOST_CHECK_CLOSE(intersection.ray_length, 20, 0.0001);
    BOOST_CHECK_CLOSE(intersection.normal.x, -1, 0.0001);
    BOOST_CHECK_CLOSE(intersection.normal.y, 0, 0.0001);
    BOOST_CHECK_CLOSE(intersection.normal.z, 0, 0.0001);

}

BOOST_AUTO_TEST_SUITE_END();
