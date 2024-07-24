#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "shapes.hpp"
#include "renderer.hpp"

namespace renderer
{
    class World
    {
    public:
        World(
            size_t view_port_width_,
            size_t view_port_height_,
            size_t super_sampling_ = 1.0) : view_port_width(view_port_width_),
                                            view_port_height(view_port_height_),
                                            super_sampling(super_sampling_)
        {
        }

        void render(Display& display);

    private:
        // View Point is origin
        int view_port_width;
        int view_port_height;

        int super_sampling;

        lin_alg::Coordinate origin = lin_alg::Coordinate(0.0, 0.0, 0.0);

        std::vector<Object> objects;
    };

};

#endif