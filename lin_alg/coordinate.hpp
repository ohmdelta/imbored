#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <vector>
#include <cassert>
#include <ostream>

namespace lin_alg
{
    class Coordinate
    {
    public:
        Coordinate(
            double x,
            double y,
            double z,
            double a = 1.0) : x(x), y(y), z(z), a(a)
        {
        }

        double operator[](int __n);

        Coordinate operator*(Coordinate b);

        friend std::ostream & operator<<(std::ostream & Str, Coordinate const & mc);

        double x;
        double y;
        double z;
        double a;
    };
}

#endif