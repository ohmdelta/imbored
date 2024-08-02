#ifndef ROTATION_HPP
#define ROTATION_HPP

#include <vector>
#include <cassert>
#include <ostream>

#include "transformation.hpp"

namespace lin_alg
{
    class Rotation : public Identity
    {
    public:
        Rotation() : Identity()
        {
        }

        void rotate_x(double angle_rad)
        {
            operator()(1, 1) = std::cos(angle_rad);
            operator()(2, 1) = std::sin(angle_rad);
            operator()(1, 2) = -operator()(2, 1);
            operator()(2, 2) = operator()(1, 1);
        }

        void rotate_y(double angle_rad)
        {
            operator()(0, 0) = std::cos(angle_rad);
            operator()(0, 2) = std::sin(angle_rad);
            operator()(2, 0) = -operator()(0, 2);
            operator()(2, 2) = operator()(0, 0);
        }

        void rotate_z(double angle_rad)
        {
            operator()(0, 0) = std::cos(angle_rad);
            operator()(1, 0) = std::sin(angle_rad);
            operator()(0, 1) = -operator()(1, 0);
            operator()(1, 1) = operator()(0, 0);
        }
    };

    class RotationX : public Rotation
    {
    public:
        RotationX() : Rotation()
        {
        }

        RotationX(double angle_rad) : Rotation()
        {
            rotate_x(angle_rad);
        }
    };

};

#endif