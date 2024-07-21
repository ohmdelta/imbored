#include "coordinate.hpp"
#include <iostream>
#include <vector>

namespace lin_alg
{
    Coordinate Coordinate::operator*(const Coordinate &b)
    {
        Coordinate n(x * b.x, y * b.y, z * b.z, a * b.a);

        return n;
    };

    Coordinate Coordinate::operator*(double p)
    {
        return Coordinate(x * p, y * p, z * p);
    };

    Coordinate Coordinate::operator*(double p) const
    {
        return Coordinate(x * p, y * p, z * p);
    };

    Coordinate Coordinate::operator+(double p)
    {
        return Coordinate(x + p, y + p, z + p);
    }

    Coordinate Coordinate::operator-(double p)
    {
        return operator+(-p);
    }

    Coordinate Coordinate::operator/(double p)
    {
        assert(p != 0);
        return operator*(1 / p);
    }

    Coordinate Coordinate::operator+(const Coordinate &b)
    {
        return Coordinate(x + b.x, y + b.y, z + b.z);
    };

    Coordinate Coordinate::operator-(const Coordinate &b)
    {
        auto v = b * -1.0;
        return *this + v;
    };

    Coordinate Coordinate::operator/(const Coordinate &b)
    {
        assert(b.x != 0 && b.y != 0 && b.z != 0);
        return Coordinate(x / b.x, y / b.y, z / b.z);
    }

    bool operator==(const Coordinate &a, const Coordinate &b)
    {
        // std::cout << "Hello THERE";
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }

    bool Coordinate::operator==(const Coordinate &b)
    {
        return x == b.x && y == b.y && z == b.z;
    }

    bool Coordinate::operator>(const Coordinate &b)
    {
        return x > b.x && y > b.y && z > b.z;
    }

    bool Coordinate::operator>=(const Coordinate &coord2)
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (operator[](i) < coord2[i])
                return false;
        }

        return true;
    }

    bool Coordinate::operator<(const Coordinate &b)
    {
        return x < b.x && y < b.y && z < b.z;
    }

    bool Coordinate::operator<=(const Coordinate &coord2)
    {
        for (size_t i = 0; i < 3; i++)
        {
            if (operator[](i) > coord2[i])
                return false;
        }

        return true;
    }

    const double &Coordinate::operator[](int __n) const
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

    double &Coordinate::operator[](int __n)
    {
        assert(__n < 3 && __n >= 0);

        switch (__n)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::range_error("Error getting operator");
        }
    }

    void Coordinate::normalise()
    {
        x /= a;
        y /= a;
        z /= a;
    }

    std::ostream &operator<<(std::ostream &Str, Coordinate &mc)
    {
        mc.normalise();

        Str << "[ " << mc.x << ", ";
        Str << mc.y << ", ";
        Str << mc.z << ", " << mc.a << " ]";
        return Str;
    }

    Coordinate &Coordinate::operator+=(double b)
    {
        for (size_t i = 0; i < 3; i++)
        {
            operator[](i) += b;
        }

        return *this;
    }

    Coordinate &Coordinate::operator-=(double b)
    {
        return operator+=(-b);
    }

    Coordinate &Coordinate::operator*=(double b)
    {
        for (size_t i = 0; i < 3; i++)
        {
            operator[](i) *= b;
        }

        return *this;
    }

    Coordinate &Coordinate::operator/=(double b)
    {
        assert(b != 0);

        for (size_t i = 0; i < 3; i++)
        {
            operator[](i) /= b;
        }

        return *this;
    }

    Coordinate &Coordinate::operator+=(const Coordinate &b)
    {
        for (size_t i = 0; i < 3; i++)
        {
            operator[](i) += b[i];
        }

        return *this;
    }

    Coordinate &Coordinate::operator-=(const Coordinate &b)
    {
        operator+=(b * -1);
        return *this;
    }

    Coordinate &Coordinate::operator*=(const Coordinate &b)
    {
        for (size_t i = 0; i < 3; i++)
        {
            operator[](i) *= b[i];
        }

        return *this;
    }

    Coordinate &Coordinate::operator/=(const Coordinate &b)
    {
        for (size_t i = 0; i < 3; i++)
        {
            assert(b[i] != 0.0);
            operator[](i) /= b[i];
        }

        return *this;
    }

}
