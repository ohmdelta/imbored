#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <vector>
#include <cassert>
#include <ostream>
#include <cmath>

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
        }

        double x;
        double y;
        double z;
        double a;

        double dot(const Vector &vector);
        double sum();

        double &operator[](int __n);
        const double &operator[](int __n) const;

        double &operator()(int __n) { return operator[](__n); };
        const double &operator()(int __n) const { return operator[](__n); };

        virtual void normalise();

        virtual double norm();
        virtual double norm_sq();

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

        friend bool operator==(const Vector &a, const Vector &b);

        friend std::ostream &operator<<(std::ostream &Str, Vector &mc);
    };

    class Coordinate : public Vector
    {
    public:
        Coordinate(
            double x_,
            double y_,
            double z_,
            double a_ = 1.0) : Vector(x_, y_, z_, a_)
        {
        }

        void normalise()
        {
            if (a == 1)
                return;

            if (a == 0)
            {
                throw std::runtime_error("Math error: Attempted to divide by Zero\n");
            }

            x /= a;
            y /= a;
            z /= a;
        }

        double norm_sq()
        {
            normalise();
            return x * x + y * y + z * z;
        }

        double norm()
        {
            return sqrt(norm_sq());
        }
    };

}

#endif