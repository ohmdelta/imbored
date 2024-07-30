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
        lin_alg::Coordinate coordinate;
        double ray_length;
        size_t id = -1;

        Intersection(
            bool valid_,
            const lin_alg::Coordinate &coordinate_,
            double ray_length_ = 0.0,
            size_t id_ = -1) : valid(valid_),
                               coordinate(coordinate_),
                               ray_length(ray_length_),
                               id(id_)
        {
        }
    };
};

#endif