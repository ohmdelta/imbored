#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <cmath>
#include <memory>

#include "lin_alg.hpp"
#include "ray.hpp"

#include "shapes.hpp"

namespace renderer
{
    struct Shape;

    struct Intersection
    {
        Intersection(
            bool valid_,
            const lin_alg::Coordinate &coordinate_ = lin_alg::Origin(),
            double ray_length_ = 0.0,
            size_t id_ = -1) : valid(valid_),
                               coordinate(coordinate_),
                               ray_length(ray_length_),
                               id(id_) {}

        bool valid;
        lin_alg::Coordinate coordinate;
        double ray_length;
        size_t id = -1;
        lin_alg::Coordinate normal = lin_alg::Origin();

        double max_length = 1000;

        Ray reflected_ray(Ray ray);
        lin_alg::Coordinate reflected_ray(lin_alg::Coordinate ray);

        friend bool operator<(const Intersection &l, const Intersection &r);
    };

}; // namespace renderer

#endif
