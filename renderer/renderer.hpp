#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <cassert>
#include <ostream>
#include <cmath>
#include <sstream>

namespace renderer
{
    struct Display
    {
        virtual unsigned char &operator()(size_t r, size_t c) = 0;
    };

    class TerminalDisplay : public Display
    {
    public:
        TerminalDisplay(size_t width_, size_t height_) : width(width_), height(height_), matrix(width_ * height_, 0)
        {
        }

        void resize(size_t width_, size_t height_);

        std::stringstream render_to_str();

        unsigned char &operator()(size_t r, size_t c);

        void clear();

    private:
        size_t width;
        size_t height;

        unsigned char val_to_char(unsigned char i);

        std::vector<unsigned char> matrix;
    };

}

#endif