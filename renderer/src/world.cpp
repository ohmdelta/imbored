#include "world.hpp"

#include <algorithm>
#include <iostream>
#include <cmath>

namespace renderer
{
    void World::render_orthographic(std::shared_ptr<Display> display)
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

    void World::render_perspective(std::shared_ptr<Display> display)
    {
        size_t width = display->width();
        size_t height = display->height();

        int min_width = std::min(width, view_port_width);
        int min_height = std::min(height, view_port_height);
        int max_pixels = min_width * min_height;

        pixel_index = 0;

        std::vector<std::thread> thread_pool;
        thread_pool.reserve(num_threads);

        auto thread_display_task = [this, min_width, min_height, max_pixels, display]()
        {
            auto width_half = min_width / 2;
            auto height_half = min_height / 2;

            for (int count{}; (count = pixel_index++) < max_pixels;)
            {
                auto v = std::div(count, min_width);
                int i = v.quot;
                int j = v.rem;

                for (size_t c = 0; c < super_sampling; c++)
                {
                    for (size_t d = 0; d < super_sampling; d++)
                    {
                        double x = i + ((double)c / super_sampling) - height_half;
                        double y = j + ((double)d / super_sampling) - width_half;
                        lin_alg::Coordinate dir(focal_point, x, y);

                        update_pixel_(dir, display,
                                      i, j,
                                      lin_alg::Coordinate(0, x, y));
                    }
                }
            }
        };

        for (size_t i = 0; i < num_threads; i++)
        {
            thread_pool.push_back(
                std::thread(
                    thread_display_task));
        }

        for (auto &thread : thread_pool)
        {
            thread.join();
        }
    }

    void World::update_pixel_(
        lin_alg::Coordinate &dir,
        std::shared_ptr<renderer::Display> display,
        size_t i, size_t j,
        const lin_alg::Coordinate &origin)
    {
        if (intersecting(dir, origin))
            display->operator()(i, j) += 255 / (super_sampling * super_sampling);
    }

    void World::update_pixel_(
        lin_alg::Coordinate &dir,
        std::shared_ptr<renderer::Display> display,
        size_t i, size_t j,
        const lin_alg::Coordinate &origin,
        double value)
    {
        if (intersecting(dir, origin))
            display->operator()(i, j) += std::floor(value * 255 / (super_sampling * super_sampling));
    }

    void World::thread_display_update_task(
        std::shared_ptr<Display> display,
        const int min_width,
        const int min_height,
        const int max_pixels)
    {
        auto width_half = min_width / 2;
        auto height_half = min_height / 2;

        for (int count{}; (count = pixel_index++) < max_pixels;)
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

                    update_pixel_(dir, display,
                                  i, j,
                                  lin_alg::Coordinate(0, x, y));
                }
            }
        }
    }

    bool World::intersecting(lin_alg::Coordinate dir,
                             const lin_alg::Coordinate &origin)
    {
        return std::any_of(
            std::begin(objects),
            std::end(objects),
            [dir, origin](std::shared_ptr<renderer::Shape> obj)
            { auto intersection = obj->line_intersection(
                            origin,
                            dir);
                return intersection.valid && intersection.ray_length > EPSILON; });
    }

    Intersection World::min_intersection(
        lin_alg::Coordinate dir,
        const lin_alg::Coordinate &origin)
    {
        std::vector<Intersection> intersections;
        intersections.reserve(objects.size());

        for (auto &obj : objects)
        {
            Intersection inter_ = obj->line_intersection(
                origin,
                dir);

            if (inter_.valid)
            {
                inter_.id = obj->id;
                intersections.push_back(std::move(inter_));
            }
        }

        if (intersections.empty())
        {
            return Intersection(false);
        }

        return *std::min_element(std::begin(intersections), std::end(intersections));
    };

    void World::set_ambient(double a)
    {
        ambient = a;
    }

    void World::ray_trace_perspective(std::shared_ptr<Display> display)
    {
        size_t width = display->width();
        size_t height = display->height();

        int min_width = std::min(width, view_port_width);
        int min_height = std::min(height, view_port_height);
        int max_pixels = min_width * min_height;

        pixel_index = 0;

        std::vector<std::thread> thread_pool;
        thread_pool.reserve(num_threads);

        auto valid_light_directions = [this](const Intersection &intersection)
        {
            auto coord = intersection.coordinate + intersection.normal;

            auto intersecting_ = [this](lin_alg::Coordinate dir,
                                        const lin_alg::Coordinate &origin)
            {
                return std::any_of(
                    std::begin(objects),
                    std::end(objects),
                    [dir, origin](std::shared_ptr<renderer::Shape> obj)
                    {
                        auto intersection = obj->line_intersection(
                            origin,
                            dir);
                        return intersection.valid && intersection.ray_length > EPSILON && intersection.ray_length < 1.0;
                    });
            };

            std::vector<lin_alg::Coordinate> intersecting;
            intersecting.reserve(light_sources.size());

            for (size_t i = 0; i < light_sources.size(); i++)
            {
                auto light_origin = light_sources[i].shape->get_origin();
                auto direction = light_origin - coord;
                if (!intersecting_(direction, coord))
                    intersecting.push_back(std::move(direction));
            }

            return intersecting;
        };

        auto thread_display_task = [this,
                                    valid_light_directions,
                                    min_width,
                                    min_height,
                                    max_pixels,
                                    display]()
        {
            int width_half = min_width / 2;
            int height_half = min_height / 2;

            for (int count{}; (count = pixel_index++) < max_pixels;)
            {
                auto v = std::div(count, min_width);
                int i = v.quot;
                int j = v.rem;

                for (size_t c = 0; c < super_sampling; c++)
                {
                    for (size_t d = 0; d < super_sampling; d++)
                    {
                        double x = i + ((double)c / super_sampling) - height_half;
                        double y = j + ((double)d / super_sampling) - width_half;
                        lin_alg::Coordinate dir(focal_point, x, y);
                        // dir.dir_normalise();
                        double L = ambient;

                        Intersection min_inter = min_intersection(dir, lin_alg::Origin());
                        if (min_inter.valid)
                        {
                            auto light_source_dir = valid_light_directions(min_inter);

                            if (light_source_dir.empty())
                            {
                                // display->operator()(i, j) += std::floor(ambient * 255 / (super_sampling * super_sampling));
                                continue;
                            }
                            for (auto &&dir_ : light_source_dir)
                            {
                                // TODO FIX Constants & Make multiple ray passes
                                min_inter.normal.dir_normalise();
                                double distance = dir_.norm_sq();

                                dir_.dir_normalise();
                                auto r = min_inter.reflected_ray(dir_);

                                auto object = objects[min_inter.id];
                                L += (std::max(min_inter.normal.dot(dir_), 0.) * object->k_diffuse + object->k_specular * std::pow(std::max(dir.dot(r), 0.), object->specular_exponent)) * (object->phi_specular / distance);
                            }
                            display->operator()(i, j) += std::floor(std::clamp(L, 0., 1.) * 255 / (super_sampling * super_sampling));

                            // double value = std::max(1.0 - num_shadow_intersections * shadow, 0.0);
                        }
                    }
                }
            }
        };

        for (size_t i = 0; i < num_threads; i++)
        {
            thread_pool.push_back(
                std::thread(
                    thread_display_task));
        }

        for (auto &thread : thread_pool)
        {
            thread.join();
        }
    }
};
