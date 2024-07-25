#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "shapes.hpp"
#include "display.hpp"
#include <lin_alg.hpp>

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

        void render(Display &display);

        void render_orthographic(Display &display)
        {
            auto width = display.width();
            auto height = display.height();

            auto min_width = std::min(width, view_port_width);
            auto min_height = std::min(height, view_port_height);

            lin_alg::Coordinate dir(1, 0, 0);

            for (size_t i = 0; i < min_height; i++)
            {
                for (size_t j = 0; j < min_width; j++)
                {
                    for (auto &obj : objects)
                    {
                        auto inter_ = obj->line_intersection(
                            lin_alg::Coordinate(0, i, j),
                            dir);
                        if (inter_.a)
                        {
                            display(i, j) = 255;
                            break;
                        }
                    }
                }
            }
        }

        void add_object(std::shared_ptr<Object> object)
        {
            objects.push_back(object);
        }

    private:
        // View Point is origin
        size_t view_port_width;
        size_t view_port_height;

        size_t super_sampling;

        lin_alg::Coordinate origin = lin_alg::Coordinate(0.0, 0.0, 0.0);

        std::vector<std::shared_ptr<Object>> objects;
    };

};

#endif