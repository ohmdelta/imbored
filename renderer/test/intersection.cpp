#define BOOST_TEST_MODULE Tests

#include <boost/test/unit_test.hpp>
#include "renderer.hpp"

BOOST_AUTO_TEST_SUITE(IntersectionSuite)

using namespace renderer;

BOOST_AUTO_TEST_CASE(IntersectionReflection)
{
    Intersection intersection(1, lin_alg::Origin(), 1);
    intersection.normal = lin_alg::Coordinate(0, 0, 1);
    
    Ray ray(lin_alg::Coordinate(1, 0, 1), lin_alg::Coordinate(-1, 0, -1));
    Ray reflected = intersection.reflected_ray(ray);

    auto gradient = reflected.line_gradient;
    BOOST_CHECK_EQUAL(gradient.x, -1);
    BOOST_CHECK_EQUAL(gradient.y, 0);
    BOOST_CHECK_EQUAL(gradient.z, 1);
    BOOST_CHECK_EQUAL(gradient.a, 1);
}

BOOST_AUTO_TEST_SUITE_END();
