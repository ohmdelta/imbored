#include "shapes.hpp"

namespace renderer
{
    lin_alg::Coordinate Sphere::line_intersection(
        const lin_alg::Coordinate &p0,
        const lin_alg::Coordinate &d)
    {
        lin_alg::Coordinate result(0, 0, 0);
        auto ps = origin;
        lin_alg::Coordinate delta_p = p0 - ps;

        double b = delta_p.dot(d);

        double a_ = delta_p.dot(delta_p);
        double b_ = delta_p.norm_sq();
        double rs_ = radius * radius;

        double v = a_ * a_ - b_ + rs_;
        if (v < 0)
        {
            result.a = 0;
            return result;
        }

        double mu = -b - sqrt(v);
        result += p0 + d * mu;
        return result;
    };
};
