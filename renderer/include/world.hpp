#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <atomic>
#include <functional>
#include <memory>
#include <thread>
#include <cstdlib>

#include "lin_alg.hpp"

#include "shapes.hpp"
#include "display.hpp"
#include "light_source.hpp"

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

        inline void add_light_source(LightSource light_source)
        {
            light_sources.push_back(light_source);
        }

        void render_orthographic(std::shared_ptr<Display> display);

        void render_perspective(std::shared_ptr<Display> display);

        void ray_trace_perspective(std::shared_ptr<Display> display);

        void set_ambient(double ambient);

    private:
        bool intersecting(lin_alg::Coordinate dir,
                          const lin_alg::Coordinate &origin);

        Intersection min_intersection(lin_alg::Coordinate dir,
                                      const lin_alg::Coordinate &origin);

        void update_pixel_(
            lin_alg::Coordinate &dir,
            std::shared_ptr<renderer::Display> display,
            size_t i, size_t j,
            const lin_alg::Coordinate &origin);

        void update_pixel_(
            lin_alg::Coordinate &dir,
            std::shared_ptr<renderer::Display> display,
            size_t i, size_t j,
            const lin_alg::Coordinate &origin,
            double value);

        void thread_display_update_task(
            std::shared_ptr<Display> display,
            const int min_width,
            const int min_height,
            const int max_pixels);

    private:
        // View Point is origin
        size_t view_port_width;
        size_t view_port_height;

        size_t super_sampling;
        double focal_point;

        lin_alg::Coordinate origin = lin_alg::Coordinate(0.0, 0.0, 0.0);

        std::vector<std::shared_ptr<Shape>> objects;
        std::vector<LightSource> light_sources;

        std::atomic_int64_t pixel_index = 0;

        size_t num_threads = 32;

        double ambient = 1.0;
        double shadow = 0.5;
    };

};

#endif