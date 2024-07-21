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
            double a = 1.0) : x(x / a), y(y / a), z(z / a)
        {
        }

        double& operator[](int __n);
        const double& operator[](int __n) const;

        void normalise();

        Coordinate operator*(const Coordinate &b);
        Coordinate operator*(double p);
        Coordinate operator+(Coordinate b);
        Coordinate operator-(Coordinate &b);

        bool operator>(const Coordinate &b);
        bool operator<(const Coordinate &b);
        bool operator>=(const Coordinate &b);
        bool operator<=(const Coordinate &b);
        bool operator==(const Coordinate &b);

        double sum();

        friend bool operator==(const Coordinate &a, const Coordinate &b);

        friend std::ostream &operator<<(std::ostream &Str, Coordinate &mc);

        double x;
        double y;
        double z;
        const double a = 1.0;
    };
}

#endif