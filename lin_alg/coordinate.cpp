#include <iostream>
#include <vector>
#include <stdexcept>

#include "coordinate.hpp"

namespace lin_alg
{
    Vector Vector::operator*(const Vector &b)
    {
        Vector n(x * b.x, y * b.y, z * b.z, a * b.a);

        return n;
    };

    Vector Vector::operator*(double p)
    {
        return Vector(x * p, y * p, z * p);
    };

    Vector Vector::operator*(double p) const
    {
        return Vector(x * p, y * p, z * p);
    };

    Vector Vector::operator+(double p)
    {
        return Vector(x + p, y + p, z + p);
    }

    Vector Vector::operator-(double p)
    {
        return operator+(-p);
    }

    Vector Vector::operator/(double p)
    {
        if (p == 0)
        {
            throw std::runtime_error("Math error: Attempted to divide by Zero\n");
        }
        return operator*(1 / p);
    }

    Vector Vector::operator+(const Vector &b)
    {
        return Vector(x + b.x, y + b.y, z + b.z);
    };

    Vector Vector::operator-(const Vector &b)
    {
        auto v = b * -1.0;
        return *this + v;
    };

    Vector Vector::operator/(const Vector &b)
    {
        if (b.x == 0 || b.y == 0 || b.z == 0)
        {
            throw std::runtime_error("Math error: Attempted to divide by Zero\n");
        }
        return Vector(x / b.x, y / b.y, z / b.z);
    }

    bool operator==(const Vector &a, const Vector &b)
    {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }

    bool Vector::operator==(const Vector &b)
    {
        return x == b.x && y == b.y && z == b.z;
    }

    bool Vector::operator>(const Vector &b)
    {
        return x > b.x && y > b.y && z > b.z;
    }

    bool Vector::operator>=(const Vector &coord2)
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (operator[](i) < coord2[i])
                return false;
        }

        return true;
    }

    bool Vector::operator<(const Vector &b)
    {
        return x < b.x && y < b.y && z < b.z;
    }

    bool Vector::operator<=(const Vector &coord2)
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (operator[](i) > coord2[i])
                return false;
        }

        return true;
    }

    const double &Vector::operator[](int __n) const
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

    double &Vector::operator[](int __n)
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

    void Vector::normalise()
    {
        if (a != 0 && a != 1)
        {
            x /= a;
            y /= a;
            z /= a;
        }
    }

    std::ostream &operator<<(std::ostream &Str, Vector &mc)
    {
        mc.normalise();

        Str << "[ " << mc.x << ", ";
        Str << mc.y << ", ";
        Str << mc.z << ", " << mc.a << " ]";
        return Str;
    }

    Vector &Vector::operator+=(double b)
    {
        for (size_t i = 0; i < 3; i++)
        {
            operator[](i) += b;
        }

        return *this;
    }

    Vector &Vector::operator-=(double b)
    {
        return operator+=(-b);
    }

    Vector &Vector::operator*=(double b)
    {
        for (size_t i = 0; i < 3; i++)
        {
            operator[](i) *= b;
        }

        return *this;
    }

    Vector &Vector::operator/=(double b)
    {
        if (b == 0)
        {
            throw std::runtime_error("Math error: Attempted to divide by Zero\n");
        }

        for (size_t i = 0; i < 3; i++)
        {
            operator[](i) /= b;
        }

        return *this;
    }

    Vector &Vector::operator+=(const Vector &b)
    {
        for (size_t i = 0; i < 3; i++)
        {
            operator[](i) += b[i];
        }

        return *this;
    }

    Vector &Vector::operator-=(const Vector &b)
    {
        operator+=(b * -1);
        return *this;
    }

    Vector &Vector::operator*=(const Vector &b)
    {
        for (size_t i = 0; i < 3; i++)
        {
            operator[](i) *= b[i];
        }

        return *this;
    }

    Vector &Vector::operator/=(const Vector &b)
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (b[i] == 0)
            {
                throw std::runtime_error("Math error: Attempted to divide by Zero\n");
            }
            operator[](i) /= b[i];
        }

        return *this;
    }

}
