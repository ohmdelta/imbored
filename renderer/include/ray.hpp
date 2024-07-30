#ifndef RAY_HPP
#define RAY_HPP

#include <cmath>
#include <memory>

#include "shapes.hpp"

namespace renderer
{
    struct Ray
    {
        lin_alg::Coordinate line_origin;
        lin_alg::Coordinate line_gradient;
        double ray_length;
    };
};

#endif