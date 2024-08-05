#include "triangle.hpp"

namespace renderer
{
    void Triangle::set_origin(const lin_alg::Coordinate &origin_)
    {
        origin = origin_;
    }

    Intersection Triangle::line_intersection(
        lin_alg::Coordinate ray_origin,
        lin_alg::Coordinate ray_vector)
    {

        auto ray_cross_e2 = ray_vector.cross(edge2);
        double det = edge1.dot(ray_cross_e2);

        if (std::abs(det) < EPSILON)
            return Intersection(false);

        double inv_det = 1.0 / det;
        auto s = ray_origin - origin;
        float u = inv_det * s.dot(ray_cross_e2);

        if (u < 0 || u > 1)
            return Intersection(false);


        auto s_cross_e1 = s.cross(edge1);

        double v = inv_det * ray_vector.dot(s_cross_e1);

        if (v < 0 || u + v > 1)
            return Intersection(false);

        double t = inv_det * edge2.dot(s_cross_e1);
        if (t > EPSILON)
        {
            Intersection intersection(true, ray_origin + ray_vector * t, t);
            intersection.normal = normal();
            return intersection;
        }
        else
        {

            return Intersection(false);
        }
    }

    lin_alg::Vector Triangle::normal()
    {
        return edge1.cross(edge2);
    }
    lin_alg::Vector Triangle::normal(const lin_alg::Coordinate &)
    {
        return normal();
    }

    void Triangle::rotate(lin_alg::TransformationMatrix t)
    {
        edge1 = t * edge1;
        edge2 = t * edge2;
    }

};
