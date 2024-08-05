#ifndef CHECKER_BOARD_HPP
#define CHECKER_BOARD_HPP

#include "lin_alg.hpp"

#include "plane.hpp"

namespace renderer
{
    struct CheckerBoard : public Plane
    {
        CheckerBoard(const lin_alg::Coordinate &origin_,
                     const lin_alg::Coordinate &normal__,
                     const lin_alg::Coordinate &grid_orientation_
                     );

        Intersection line_intersection(
            lin_alg::Coordinate l0,
            lin_alg::Coordinate l) override;

    private:
        lin_alg::Coordinate grid_orientation_x;
        lin_alg::Coordinate grid_orientation_y = lin_alg::Coordinate(0, 1, 0);
    };
};

#endif