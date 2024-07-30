#include "sphere.hpp"
#include <iostream>

namespace renderer
{
    Intersection Sphere::line_intersection(
        lin_alg::Coordinate p0,
        lin_alg::Coordinate d)
    {
        lin_alg::Coordinate result(0, 0, 0);
        auto ps = origin;
        lin_alg::Coordinate delta_p = p0 - ps;

        double a = d.norm_sq();
        double b = 2 * d.dot(delta_p);
        double c = delta_p.norm_sq() - radius * radius;

        double v = b * b - 4 * a * c;
        if (v < 0)
        {
            result.a = 0;
            // return result;
            return Intersection(false, result);
        }

        double mu = (-b - sqrt(v)) / (2 * a);

        lin_alg::Coordinate d_ = (d * mu);
        result += (p0 + d_);
        return Intersection(true, result, mu);
    };
};
