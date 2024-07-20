#include "transformation.hpp"

namespace lin_alg
{
    Coordinate operator*(
        Transformation &transformation,
        const Coordinate &coord)
    {
        return transformation.X * coord.x +
               transformation.Y * coord.y +
               transformation.Z * coord.z +
               transformation.A * coord.a;
    }
}
