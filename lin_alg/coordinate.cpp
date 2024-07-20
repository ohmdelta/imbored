#include "coordinate.hpp"
#include <iostream>

namespace lin_alg
{
    Coordinate Coordinate::operator*(const Coordinate &b)
    {
        return Coordinate(x * b.x, y * b.y, z * b.z, a * b.a);
    };

    Coordinate Coordinate::operator*(double p)
    {
        return Coordinate(x * p, y * p, z * p, a);
    };

    Coordinate Coordinate::operator+(Coordinate b)
    {
        normalise();
        b.normalise();

        return Coordinate(x + b.x, y + b.y, z + b.z);
    };

    Coordinate Coordinate::operator-(Coordinate& b)
    {
        normalise();
        b.normalise();

        return *this + b * -1;
    };

    bool operator==(Coordinate &a, Coordinate &b)
    {
        a.normalise();
        b.normalise();
        std::cout << "Hello THERE";

        return a.x == b.x && a.y == b.y && a.z == b.z;
    }

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

    void Coordinate::normalise()
    {
        x /= a;
        y /= a;
        z /= a;
        a = 1;
    }

    std::ostream &operator<<(std::ostream &Str, Coordinate &mc)
    {
        mc.normalise();

        Str << "[ " << mc.x << ", ";
        Str << mc.y << ", ";
        Str << mc.z << ", " << mc.a << " ]";
        return Str;
    }
}
