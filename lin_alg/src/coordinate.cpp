#include "coordinate.hpp"

namespace lin_alg
{
    Coordinate Coordinate::cross(Coordinate &coordinate)
    {
        coordinate.normalise();
        normalise();

        Coordinate result(0, 0, 0);

        result.x = y * coordinate.z - z * coordinate.y;
        result.y = z * coordinate.x - x * coordinate.z;
        result.z = x * coordinate.y - y * coordinate.x;

        return result;
    }

}
