#define BOOST_TEST_MODULE Tests

#include <boost/test/unit_test.hpp>
#include "renderer.hpp"

using namespace renderer;

BOOST_AUTO_TEST_SUITE(shape_suite);

BOOST_AUTO_TEST_CASE(sphere_intersection)
{
    renderer::Sphere sphere(1.0, lin_alg::Coordinate(2, 0, 0));
    auto intersection = sphere.line_intersection(
        lin_alg::Origin(),
        lin_alg::Coordinate(1, 0, 0)).coordinate;
    
    BOOST_CHECK_CLOSE(intersection.x, 1.0, 0.001);
    BOOST_CHECK_CLOSE(intersection.y, 0.0, 0.001);
    BOOST_CHECK_CLOSE(intersection.z, 0.0, 0.001);
    BOOST_CHECK_CLOSE(intersection.a, 1.0, 0.001);

    auto intersection2 = sphere.line_intersection(
        lin_alg::Coordinate(0, 0, 1),
        lin_alg::Coordinate(1, 0, 0)).coordinate;

    BOOST_CHECK_CLOSE(intersection2.x, 2.0, 0.001);
    BOOST_CHECK_CLOSE(intersection2.y, 0.0, 0.001);
    BOOST_CHECK_CLOSE(intersection2.z, 1.0, 0.001);
    BOOST_CHECK_CLOSE(intersection2.a, 1.0, 0.001);

    auto intersection3 = sphere.line_intersection(
        lin_alg::Coordinate(0, 0, 2),
        lin_alg::Coordinate(1, 0, 0));
    
    BOOST_CHECK(!intersection3.valid);
 
}

BOOST_AUTO_TEST_SUITE_END();
