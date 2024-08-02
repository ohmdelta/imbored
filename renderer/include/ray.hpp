#ifndef RAY_HPP
#define RAY_HPP

#include <cmath>
#include <memory>

#include "lin_alg.hpp"

namespace renderer
{
    struct Ray
    {
        lin_alg::Coordinate line_origin;
        lin_alg::Coordinate line_gradient;
        double ray_length = 0;

        Ray(lin_alg::Coordinate line_origin_,
            lin_alg::Coordinate line_gradient_,
            double ray_length_ = 0) : line_origin(line_origin_),
                                      line_gradient(line_gradient_),
                                      ray_length(ray_length_) {};
    };
};

#endif