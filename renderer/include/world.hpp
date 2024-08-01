#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <atomic>
#include <functional>
#include <memory>
#include <thread>
#include <cstdlib>

#include "shapes.hpp"
#include "display.hpp"
#include "lin_alg.hpp"

namespace renderer
{
    class World
    {
    public:
        World(
            size_t view_port_width_,
            size_t view_port_height_,
            size_t super_sampling_ = 1.0,
            double focal_point_ = 100) : view_port_width(view_port_width_),
                                         view_port_height(view_port_height_),
                                         super_sampling(super_sampling_),
                                         focal_point(focal_point_)
        {
        }

        inline void add_object(std::shared_ptr<Shape> object)
        {
            objects.push_back(object);
        }

        void render(Display &display);

        void render_orthographic(std::shared_ptr<Display> display)
        {
            auto width = display->width();
            auto height = display->height();

            auto min_width = std::min(width, view_port_width);
            auto min_height = std::min(height, view_port_height);

            lin_alg::Coordinate dir(1, 0, 0);

            for (size_t i = 0; i < min_height; i++)
            {
                for (size_t j = 0; j < min_width; j++)
                {
                    for (size_t c = 0; c < super_sampling; c++)
                    {
                        for (size_t d = 0; d < super_sampling; d++)
                        {
                            auto x = i + ((double)c / super_sampling);
                            auto y = j + ((double)d / super_sampling);

                            update_pixel_(dir, display,
                                          i, j,
                                          lin_alg::Coordinate(0, x, y));
                        }
                    }
                }
            }
        }


        void render_perspective(std::shared_ptr<Display> display)
        {
            size_t width = display->width();
            size_t height = display->height();

            size_t min_width = std::min(width, view_port_width);
            size_t min_height = std::min(height, view_port_height);
            size_t max_pixels = min_width * min_height;

            pixel_index = 0;

            std::vector<std::thread> thread_pool;
            thread_pool.reserve(num_threads);

            for (size_t i = 0; i < num_threads; i++)
            {
                thread_pool.push_back(
                    std::thread(
                        &World::update_display,
                        this,
                        std::ref(display),
                        min_width,
                        min_height,
                        max_pixels));
            }

            for (auto &thread : thread_pool)
            {
                thread.join();
            }
        }

        void update_pixel_(
            lin_alg::Coordinate &dir,
            std::shared_ptr<renderer::Display> display,
            size_t i, size_t j,
            const lin_alg::Coordinate &origin)
        {
            for (auto &obj : objects)
            {
                auto inter_ = obj->line_intersection(
                    origin,
                    dir);

                if (inter_.valid)
                {
                    display->operator()(i, j) += 255 / (super_sampling * super_sampling);
                    break;
                }
            }
        }

    private:
        void update_display(
            std::shared_ptr<Display> display,
            const int min_width,
            const int min_height,
            const int max_pixels)
        {
            auto width_half = min_width / 2;
            auto height_half = min_height / 2;

            for (int count = 0; (count = pixel_index++) < max_pixels;)
            {
                auto v = std::div(count, min_width);
                size_t i = v.quot;
                size_t j = v.rem;

                for (size_t c = 0; c < super_sampling; c++)
                {
                    for (size_t d = 0; d < super_sampling; d++)
                    {
                        double x = i + ((double)c / super_sampling) - height_half;
                        double y = j + ((double)d / super_sampling) - width_half;
                        lin_alg::Coordinate dir(focal_point, x, y);

                        for (const auto &obj : objects)
                        {
                            auto inter_ = obj->line_intersection(
                                origin,
                                dir);

                            if (inter_.valid)
                            {
                                display->operator()(i, j) += 255 / (super_sampling * super_sampling);
                                break;
                            }
                        }
                    }
                }
            }
        }

    private:
        // View Point is origin
        size_t view_port_width;
        size_t view_port_height;

        size_t super_sampling;
        double focal_point;

        lin_alg::Coordinate origin = lin_alg::Coordinate(0.0, 0.0, 0.0);

        std::vector<std::shared_ptr<Shape>> objects;
        std::atomic_int64_t pixel_index = 0;

        size_t num_threads = 32;
    };

};

#endif