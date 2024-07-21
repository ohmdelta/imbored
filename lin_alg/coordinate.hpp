#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <vector>
#include <cassert>
#include <ostream>

namespace lin_alg
{
    class Vector
    {
    public:
        Vector(
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

        Vector operator*(double p);
        Vector operator*(double p) const;

        Vector operator+(double p);
        Vector operator-(double p);

        Vector operator/(double p);

        Vector operator+(const Vector &b);
        Vector operator-(const Vector &b);
        Vector operator*(const Vector &b);
        Vector operator/(const Vector &b);

        bool operator>(const Vector &b);
        bool operator<(const Vector &b);
        bool operator>=(const Vector &b);
        bool operator<=(const Vector &b);
        bool operator==(const Vector &b);

        Vector &operator+=(double b);
        Vector &operator-=(double b);
        Vector &operator*=(double b);
        Vector &operator/=(double b);

        Vector &operator+=(const Vector &b);
        Vector &operator-=(const Vector &b);
        Vector &operator*=(const Vector &b);
        Vector &operator/=(const Vector &b);

        double sum();

        friend bool operator==(const Vector &a, const Vector &b);

        friend std::ostream &operator<<(std::ostream &Str, Vector &mc);
    };
}

#endif