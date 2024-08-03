#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <cmath>

#include "lin_alg.hpp"

#include "intersection.hpp"

namespace renderer
{
    struct Intersection;
    const double EPSILON = 1e-7;

    struct ObjectProjection
    {
        virtual lin_alg::Coordinate point_projection(
            const lin_alg::Coordinate &c) = 0;
    };

    struct Shape
    {
        size_t id = -1;

        double k_diffuse = 0.5;
        double k_specular = 0.5;
        double specular_exponent = 0.4;
        double phi_specular = 50000 / (4 * M_PI);

        Shape() = default;

        // Origin
        virtual void set_origin(const lin_alg::Coordinate &) = 0;
        virtual lin_alg::Coordinate get_origin() = 0;

        // Get Shape Normal at Surface
        virtual lin_alg::Vector normal(const lin_alg::Coordinate &c) = 0;

        virtual Intersection line_intersection(
            lin_alg::Coordinate line_origin,
            lin_alg::Coordinate line_gradient) = 0;
    };

};

#endif