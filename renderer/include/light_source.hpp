#ifndef LIGHT_SOURCE_HPP
#define LIGHT_SOURCE_HPP

#include <cmath>
#include <memory>

#include "shapes.hpp"

namespace renderer
{
    struct LightSource
    {
        size_t id;
        double intensity;
        std::shared_ptr<Shape> shape;

        LightSource(
            size_t id_,
            double intensity_,
            std::shared_ptr<Shape> shape_) : id(id_),
                                             intensity(intensity_),
                                             shape(shape_) {}
    };
};

#endif