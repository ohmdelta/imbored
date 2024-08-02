#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <vector>
#include <cassert>
#include <ostream>
#include <cmath>

namespace lin_alg
{
    struct Vector
    {
        Vector(
            double x_,
            double y_,
            double z_,
            double a_ = 1.0) : x(x_), y(y_), z(z_), a(a_)
        {
        }

        double x = 0;
        double y = 0;
        double z = 0;
        double a;

        virtual bool valid() { return true; };

        virtual double dot(const Vector &vector);
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

        friend Vector operator+(const Vector &t, const Vector &p);
        friend Vector operator-(const Vector &t, const Vector &p);
        friend Vector operator*(const Vector &t, const Vector &p);
        friend Vector operator/(const Vector &t, const Vector &p);

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

    struct Coordinate : public Vector
    {
        Coordinate(
            double x_,
            double y_,
            double z_,
            double a_ = 1.0) : Vector(x_, y_, z_, a_)
        {
            normalise();
        }

        friend Coordinate operator+(Coordinate lhs, Coordinate rhs)
        {
            lhs.normalise();
            rhs.normalise();

            lhs.x += rhs.x;
            lhs.y += rhs.y;
            lhs.z += rhs.z;

            return lhs;
        }

        friend Coordinate operator-(Coordinate lhs, Coordinate &rhs)
        {
            lhs.normalise();
            rhs.normalise();

            lhs.x -= rhs.x;
            lhs.y -= rhs.y;
            lhs.z -= rhs.z;

            return lhs;
        }

        friend Coordinate operator*(Coordinate lhs, double rhs)
        {
            lhs.normalise();

            lhs.x *= rhs;
            lhs.y *= rhs;
            lhs.z *= rhs;

            return lhs;
        }

        Coordinate(Vector const &v) : Vector(v)
        {
            normalise();
        }

        void dir_normalise()
        {
            operator/=(norm());
        }

        void normalise() override
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
            a = 1;
        }

        double norm_sq() override
        {
            normalise();
            return x * x + y * y + z * z;
        }

        double norm() override
        {
            return sqrt(norm_sq());
        }

        friend std::ostream &operator<<(std::ostream &Str, Coordinate &mc)
        {
            mc.normalise();

            Str << "[ " << mc.x << ", ";
            Str << mc.y << ", ";
            Str << mc.z << " ], " << mc.a;
            return Str;
        }

        bool valid() override
        {
            return a != 0;
        }

        double dot(Coordinate coordinate)
        {
            coordinate.normalise();
            normalise();

            return x * coordinate.x + y * coordinate.y + coordinate.z * z;
        }

        Coordinate cross(Coordinate &coordinate);
    };

    struct Origin : public Coordinate
    {
        Origin() : Coordinate(0, 0, 0) {}
    };
}

#endif