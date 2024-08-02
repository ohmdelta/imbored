#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <cmath>
#include <memory>

#include "ray.hpp"
#include "lin_alg.hpp"

namespace renderer
{
    struct Intersection
    {
        Intersection(
            bool valid_,
            const lin_alg::Coordinate &coordinate_ = lin_alg::Coordinate(0, 0, 0),
            double ray_length_ = 0.0,
            size_t id_ = -1) : valid(valid_),
                               coordinate(coordinate_),
                               ray_length(ray_length_),
                               id(id_)
        {
        }

        bool valid;
        lin_alg::Coordinate coordinate;
        double ray_length;
        size_t id = -1;
        lin_alg::Coordinate normal = lin_alg::Coordinate(0, 0, 0);

        double max_length = 1000;

        Ray reflected_ray(Ray ray);

        friend bool operator<(const Intersection &l, const Intersection &r);
    };
};

#endif