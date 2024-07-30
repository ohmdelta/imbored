#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <cmath>

#include "lin_alg.hpp"

#include "intersection.hpp"

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

        virtual Intersection line_intersection(
            lin_alg::Coordinate line_origin,
            lin_alg::Coordinate line_gradient) = 0;
    };

};

#endif