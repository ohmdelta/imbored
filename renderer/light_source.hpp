#ifndef LIGHT_SOURCE_HPP
#define LIGHT_SOURCE_HPP

#include <cmath>
#include <memory>

#include "shapes.hpp"

namespace renderer
{
    struct light_source
    {
        size_t id;
        double intensity;
        std::shared_ptr<Shape> shape;
    };
};

#endif