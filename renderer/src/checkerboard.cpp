#include "checkerboard.hpp"
#include <iostream>

namespace renderer
{
    Intersection CheckerBoard::line_intersection(
        lin_alg::Coordinate p0,
        lin_alg::Coordinate l)
    {
        Intersection intersection = Plane::line_intersection(p0, l);

        if(!intersection.valid) {
            return intersection;
        }

        lin_alg::Coordinate direction = intersection.coordinate - origin;
        direction.a = 1.0;

        // std::cout << direction << std::endl;
        
        int x = std::ceil(direction.dot(grid_orientation_x));
        int y = std::ceil(direction.dot(grid_orientation_y));
        
        x &= 1;
        y &= 1;

        if (x == y) {
            return Intersection(false);
        }
        return intersection;
    }


}
