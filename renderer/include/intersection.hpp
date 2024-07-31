#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <cmath>
#include <memory>

#include "shapes.hpp"
#include "ray.hpp"
#include "lin_alg.hpp"

namespace renderer
{
    struct Intersection
    {
        bool valid;
        lin_alg::Coordinate coordinate;
        double ray_length;
        size_t id = -1;
        lin_alg::Coordinate normal = lin_alg::Coordinate(0, 0, 0);

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

        Ray reflected_ray(Ray ray)
        {
            lin_alg::Coordinate &v = ray.line_gradient;

            ray.line_origin = coordinate;
            v = v - normal * (2 * (v.dot(normal)));

            return ray;
        }

        friend bool operator<(const Intersection &l, const Intersection &r);
    };
};

#endif