#include "checkerboard.hpp"
#include <iostream>

namespace renderer
{
    CheckerBoard::CheckerBoard(const lin_alg::Coordinate &origin_,
                               const lin_alg::Coordinate &normal__,
                               const lin_alg::Coordinate &grid_orientation_) : Plane(origin_, normal__),
                                                                               grid_orientation_x(grid_orientation_)
    {
        grid_orientation_y = Plane::normal_.cross(grid_orientation_x);
    };

    Intersection CheckerBoard::line_intersection(
        lin_alg::Coordinate p0,
        lin_alg::Coordinate l)
    {
        Intersection intersection = Plane::line_intersection(p0, l);

        if (!intersection.valid)
        {
            return intersection;
        }

        lin_alg::Coordinate direction = intersection.coordinate - origin;
        direction.a = 1.0;

        int x = std::ceil(direction.dot(grid_orientation_x));
        int y = std::ceil(direction.dot(grid_orientation_y));

        x &= 1;
        y &= 1;

        if (x == y)
        {
            return Intersection(false);
        }
        return intersection;
    }

}
