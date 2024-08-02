#include <iostream>
#include <vector>
#include <stdexcept>

#include "plane.hpp"

namespace renderer
{
    void Plane::set_origin(const lin_alg::Coordinate &origin_)
    {
        origin = origin_;
    }

    Intersection Plane::line_intersection(
        lin_alg::Coordinate p0,
        lin_alg::Coordinate l)
    {
        double v = (l.dot(normal_));
        if (v == 0)
        {
            return Intersection(false);
        }

        double d = (origin - p0).dot(normal_) / v;
        if (d < EPSILON)
        {
            return Intersection(false);
        }

        lin_alg::Coordinate l_ = (l * d);
        
        Intersection intersection(true, p0 + l_, d);
        intersection.normal = normal_;
        return intersection;
    }

    lin_alg::Vector Plane::normal(const lin_alg::Coordinate &)
    {
        return normal_;
    }

}
