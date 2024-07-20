#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

#include <vector>
#include <cassert>
#include <ostream>

#include "coordinate.hpp"

namespace lin_alg
{
    class Transformation
    {
    public:
        Transformation(
            Coordinate x,
            Coordinate y,
            Coordinate z,
            Coordinate a) : X(x), Y(y), Z(z), A(a) {}
        
        Coordinate X;
        Coordinate Y;
        Coordinate Z;
        Coordinate A;

        friend Coordinate operator*(
            Transformation& transformation,
            Coordinate& coord);

    };
}

#endif