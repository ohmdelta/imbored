#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <lin_alg.hpp>
#include <cmath>

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

        lin_alg::Coordinate line_intersection(const lin_alg::Coordinate &p0, const lin_alg::Coordinate &d);
    };

    class Plane : public Object
    {
        lin_alg::Coordinate origin;
        lin_alg::Vector normal_;

        lin_alg::Vector normal(const lin_alg::Coordinate &)
        {
            return normal_;
        }

        lin_alg::Coordinate line_intersection(
            const lin_alg::Coordinate &line_origin,
            const lin_alg::Coordinate &line_gradient);
    };
};

#endif