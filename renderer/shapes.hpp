#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <lin_alg.hpp>

namespace renderer
{
    struct ObjectProjection
    {
        virtual lin_alg::Coordinate point_projection(
            const lin_alg::Coordinate &c) = 0;
    };

    struct Object
    {
        virtual void set_origin() = 0;
        virtual lin_alg::Vector normal(const lin_alg::Coordinate &c) = 0;

        virtual lin_alg::Coordinate line_intersection(
            const lin_alg::Coordinate &line_origin,
            const lin_alg::Coordinate &line_gradient) = 0;
    };

    class Sphere : public Object
    {
        lin_alg::Coordinate origin;
        double radius;

        lin_alg::Vector normal(const lin_alg::Coordinate &c)
        {
            return (origin - c) * -1;
        }

        lin_alg::Coordinate line_intersection(const lin_alg::Coordinate &line_origin, const lin_alg::Coordinate &line_gradient)
        {
            // x ^2 + y^2 + z ^2 = r^2
            // A (x - a) + B(y - b) + C(z - c) = 0
        }
    };

    class Plane : public Object
    {
        lin_alg::Coordinate origin;
        lin_alg::Vector normal;

        lin_alg::Vector normal(const lin_alg::Coordinate &c)
        {
            return normal;
        }

        lin_alg::Coordinate line_intersection(
            const lin_alg::Coordinate &line_origin,
            const lin_alg::Coordinate &line_gradient)
        {
            // x ^2 + y^2 + z ^2 = r^2
            // A (x - a) + B(y - b) + C(z - c) = 0
        }
    };
};

#endif