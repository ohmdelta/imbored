#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <cmath>

#include "lin_alg.hpp"

namespace renderer
{
    struct ObjectProjection
    {
        virtual lin_alg::Coordinate point_projection(
            const lin_alg::Coordinate &c) = 0;
    };

    struct Shape
    {
        Shape() = default;

        virtual void set_origin(const lin_alg::Coordinate &) = 0;
        virtual lin_alg::Vector normal(const lin_alg::Coordinate &c) = 0;

        virtual lin_alg::Coordinate line_intersection(
            lin_alg::Coordinate line_origin,
            lin_alg::Coordinate line_gradient) = 0;
    };

    struct Sphere : public Shape
    {
        Sphere(
            double radius_ = 0.0,
            const lin_alg::Coordinate &origin_ = lin_alg::Coordinate(0, 0, 0)) : radius(radius_), origin(origin_)
        {
        }

        void set_origin(const lin_alg::Coordinate &origin_) override
        {
            origin = origin_;
        }

        lin_alg::Vector normal(const lin_alg::Coordinate &c) override
        {
            return (origin - c) * -1;
        }

        lin_alg::Coordinate line_intersection(
            lin_alg::Coordinate p0,
            lin_alg::Coordinate d) override;

    private:
        double radius;
        lin_alg::Coordinate origin;
    };

    class Plane : public Shape
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