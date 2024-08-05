#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>

#include "shapes.hpp"

namespace renderer
{
    struct Sphere : public Shape
    {
        Sphere(
            double radius_ = 0.0,
            const lin_alg::Coordinate &origin_ = lin_alg::Origin()) : radius(radius_), origin(origin_)
        {
        }

        void set_origin(const lin_alg::Coordinate &origin_) override
        {
            origin = origin_;
        }

        lin_alg::Coordinate get_origin() override
        {
            return origin;
        }

        lin_alg::Vector normal(const lin_alg::Coordinate &c) override
        {
            return (origin - c) * -1;
        }

        Intersection line_intersection(
            lin_alg::Coordinate p0,
            lin_alg::Coordinate d) override;

    private:
        double radius;
        lin_alg::Coordinate origin;
    };

};

#endif