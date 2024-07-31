#include "intersection.hpp"

namespace renderer
{

    Ray Intersection::reflected_ray(Ray ray)
    {
        lin_alg::Coordinate &v = ray.line_gradient;

        ray.line_origin = coordinate;
        v = v - normal * (2 * (v.dot(normal)));

        return ray;
    }

    inline bool operator<(const Intersection &l, const Intersection &r)
    {
        if (!l.valid)
        {
            return false;
        }

        return l.ray_length < r.ray_length;
    }

};
