#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <cmath>
#include <memory>

#include "shapes.hpp"
#include "lin_alg.hpp"

namespace renderer
{
    struct Intersection
    {
        bool valid;
        size_t id;
        double ray_length;
        lin_alg::Coordinate coordinate;
    };
};

#endif