#ifndef TORUS_HPP
#define TORUS_HPP

#include <lin_alg.hpp>

#include "shapes.hpp"

namespace renderer
{
    class Torus : public Shape
    {
        void set_origin(const lin_alg::Coordinate &origin_)
        {
            origin = origin_;
        }

        lin_alg::Vector normal(const lin_alg::Coordinate &c)
        {
            // TODO: FIX THIS
            return (origin - c) * -1;
        }

        lin_alg::Coordinate line_intersection(
            lin_alg::Coordinate p0,
            lin_alg::Coordinate d)
        {
            // TODO: FIX THIS
            lin_alg::Coordinate v(0, 0, 0);
            return v;
        }

    private:
        double ring_radius;
        double torus_radius;

        lin_alg::Coordinate origin;
    };
};

#endif