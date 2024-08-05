#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <lin_alg.hpp>

#include "shapes.hpp"
#include "polynomial.hpp"

namespace renderer
{

    struct Triangle : public Shape
    {
        Triangle(
            lin_alg::Coordinate side_a,
            lin_alg::Coordinate side_b) : edge1(side_a),
                                          edge2(side_b)
        {
        }

        Intersection line_intersection(
            lin_alg::Coordinate p0,
            lin_alg::Coordinate d) override;

        lin_alg::Coordinate get_origin() override
        {
            return origin;
        }

        void set_origin(const lin_alg::Coordinate &origin_) override;

        lin_alg::Vector normal(const lin_alg::Coordinate &) override;
        void rotate(lin_alg::TransformationMatrix t);

    private:
        lin_alg::Coordinate edge1;
        lin_alg::Coordinate edge2;
        
        lin_alg::Vector normal() ;

        lin_alg::Coordinate origin = lin_alg::Origin();
    };

};

#endif