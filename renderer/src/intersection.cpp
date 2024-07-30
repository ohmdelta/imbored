#include "intersection.hpp"

namespace renderer
{
    inline bool operator<(const Intersection &l, const Intersection &r)
    {
        if (!l.valid)
        {
            return false;
        }

        return l.ray_length < r.ray_length;
    }

};
