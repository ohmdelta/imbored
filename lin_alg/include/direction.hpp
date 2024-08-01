#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include "coordinate.hpp"

namespace lin_alg
{
    struct Direction : public Vector
    {
        Direction(
            double x_,
            double y_,
            double z_,
            double a_ = 1.0) : Vector(x_, y_, z_, a_)
        {
            normalise();
        }

    };

}

#endif