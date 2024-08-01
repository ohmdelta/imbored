#ifndef PLANE_HPP
#define PLANE_HPP

#include "lin_alg.hpp"

#include "shapes.hpp"

namespace renderer
{
    struct Plane : public Shape
    {
        Plane(const lin_alg::Coordinate &origin_,
              const lin_alg::Coordinate &normal__) : origin(origin_),
                                                     normal_(normal__) {}

        void set_origin(const lin_alg::Coordinate &origin_) override;

        lin_alg::Vector normal(const lin_alg::Coordinate &c) override;

        virtual Intersection line_intersection(
            lin_alg::Coordinate l0,
            lin_alg::Coordinate l) override;

    protected:
        lin_alg::Coordinate origin;
        lin_alg::Coordinate normal_;
    };
};

#endif