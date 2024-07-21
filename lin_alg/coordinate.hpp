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
            double x_,
            double y_,
            double z_,
            double a_ = 1.0) : x(x_), y(y_), z(z_), a(a_)
        {
            if (a != 0)
            {
                normalise();
            }
        }

        double x;
        double y;
        double z;
        double a;

        double &operator[](int __n);
        const double &operator[](int __n) const;

        double &operator()(int __n) { return operator[](__n); };
        const double &operator()(int __n) const { return operator[](__n); };

        void normalise();

        Coordinate operator*(double p);
        Coordinate operator*(double p) const;

        Coordinate operator+(double p);
        Coordinate operator-(double p);

        Coordinate operator/(double p);

        Coordinate operator+(const Coordinate &b);
        Coordinate operator-(const Coordinate &b);
        Coordinate operator*(const Coordinate &b);
        Coordinate operator/(const Coordinate &b);

        bool operator>(const Coordinate &b);
        bool operator<(const Coordinate &b);
        bool operator>=(const Coordinate &b);
        bool operator<=(const Coordinate &b);
        bool operator==(const Coordinate &b);

        Coordinate &operator+=(double b);
        Coordinate &operator-=(double b);
        Coordinate &operator*=(double b);
        Coordinate &operator/=(double b);

        Coordinate &operator+=(const Coordinate &b);
        Coordinate &operator-=(const Coordinate &b);
        Coordinate &operator*=(const Coordinate &b);
        Coordinate &operator/=(const Coordinate &b);

        double sum();

        friend bool operator==(const Coordinate &a, const Coordinate &b);

        friend std::ostream &operator<<(std::ostream &Str, Coordinate &mc);
    };
}

#endif