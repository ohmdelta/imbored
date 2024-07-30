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

    lin_alg::Coordinate Plane::line_intersection(
        lin_alg::Coordinate p0,
        lin_alg::Coordinate l)
    {
        double v = (l.dot(normal_));
        if (v == 0)
        {
            auto c = lin_alg::Coordinate(0, 0, 0);
            c.a = 0;
            return c;
        }

        double d = (origin - p0).dot(normal_) / v;
        if (d < 0)
        {
            auto c = lin_alg::Coordinate(0, 0, 0);
            c.a = 0;
            return c;
        }

        lin_alg::Coordinate l_ = (l * d);
        return p0 + l_;
    }

    lin_alg::Vector Plane::normal(const lin_alg::Coordinate &)
    {
        return normal_;
    }

}
