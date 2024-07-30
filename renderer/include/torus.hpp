#ifndef TORUS_HPP
#define TORUS_HPP

#include <lin_alg.hpp>

#include "shapes.hpp"
#include "polynomial.hpp"

namespace renderer
{
    inline double sq(double v) { return v * v; }
    inline double cube(double v) { return v * v * v; }
    inline double supercube(double v) { return sq(v) * sq(v); }

    struct Torus : public Shape
    {
        Torus(
            double ring_radius_,
            double torus_radius_,
            lin_alg::Coordinate origin_ = lin_alg::Coordinate(0, 0, 0)) : ring_radius(ring_radius_),
                                                                          torus_radius(torus_radius_),
                                                                          origin(origin_) {}

        void set_origin(const lin_alg::Coordinate &origin_) override;

        lin_alg::Vector normal(const lin_alg::Coordinate &c) override;
        
        void set_rotation(lin_alg::TransformationMatrix t);
        
        lin_alg::Coordinate line_intersection(
            lin_alg::Coordinate p0,
            lin_alg::Coordinate d) override;

    private:
        double ring_radius;
        double torus_radius;

        lin_alg::Coordinate origin;

        lin_alg::TransformationMatrix rotation = lin_alg::Identity();
    };
};

#endif