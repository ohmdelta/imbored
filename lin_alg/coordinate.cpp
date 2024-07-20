#include "coordinate.hpp"

namespace lin_alg
{
    Coordinate Coordinate::operator*(Coordinate b)
    {
        return Coordinate(x * b.x, y * b.y, z * b.z, a * b.a);
    };

    double Coordinate::operator[](int __n)
    {
        assert(__n < 4 && __n >= 0);

        switch (__n)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            return a;
        }
    }

    std::ostream &operator<<(std::ostream &Str, Coordinate const &mc)
    {
        Str << "[ " << mc.x << ", ";
        Str << mc.y << ", ";
        Str << mc.z << ", " << mc.a << " ]";
        return Str;
    }
}
