#ifdef STAND_ALONE
#define BOOST_TEST_MODULE Tests
#endif

#include <boost/test/unit_test.hpp>
#include "../renderer/renderer.hpp"

using namespace renderer;

BOOST_AUTO_TEST_SUITE(shape_suite);

BOOST_AUTO_TEST_CASE(transformation_equality)
{
    renderer::Sphere sphere(1.0, lin_alg::Coordinate(2, 0, 0));
    auto intersection = sphere.line_intersection(
        lin_alg::Coordinate(0, 0, 0),
        lin_alg::Coordinate(1, 0, 0));
    BOOST_CHECK_CLOSE(intersection.y, 0.0, 1);
    BOOST_CHECK_CLOSE(intersection.z, 0.0, 1);
    BOOST_CHECK_CLOSE(intersection.x, 1.0, 1);

}

BOOST_AUTO_TEST_SUITE_END();
