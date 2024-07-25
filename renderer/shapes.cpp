#include "shapes.hpp"
#include <iostream>

namespace renderer
{
    lin_alg::Coordinate Sphere::line_intersection(
        lin_alg::Coordinate p0,
        lin_alg::Coordinate d)
    {
        lin_alg::Coordinate result(0, 0, 0);
        auto ps = origin;
        lin_alg::Coordinate delta_p = p0 - ps;
        
        // std::cout << delta_p << std::endl;
        
        // double b = delta_p.dot(d);
        // auto d_ = lin_alg::Coordinate(d);
        // std::cout << b << ":" << d_ << std::endl;

        double a = d.norm_sq(); 
        double b = 2 * d.dot(delta_p);
        double c = delta_p.norm_sq() - radius * radius;

        double v = b * b -  4 * a * c;
        // double v = a_ - b_ + rs_;
        if (v < 0)
        {
            result.a = 0;
            return result;
        }

        double mu = (-b - sqrt(v)) / (2 * a);

        result += p0 + d * mu;
        return result;
    };
};
