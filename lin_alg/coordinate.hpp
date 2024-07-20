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

        double operator[](int __n)
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

        Coordinate operator*(Coordinate b)
        {
            return Coordinate(x * b.x, y * b.y, z * b.z, a * b.a);
        };

        friend std::ostream & operator<<(std::ostream & Str, Coordinate const & mc) { 
            Str << "[ " << mc.x << ", ";
            Str << mc.y << ", " ;
            Str << mc.z << ", " << mc.a << " ]";
            return Str;
        }

        double x;
        double y;
        double z;
        double a;
    };
}