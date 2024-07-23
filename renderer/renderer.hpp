#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <cassert>
#include <ostream>
#include <cmath>
#include <sstream>

namespace renderer
{
    class TerminalRenderer
    {
    public:
        TerminalRenderer(size_t width_, size_t height_) : width(width_), height(height_), matrix(width_ * height_, 0)
        {
        }

        void resize(size_t width_, size_t height_)
        {
            matrix.resize(width_ * height_);
        }

        std::stringstream render_to_str()
        {
            std::stringstream ss;
            for (size_t r = 0; r < height; r++)
            {
                for (size_t c = 0; c < width; c++)
                {
                    ss << val_to_char(matrix[c + r * width]);
                }
                ss << std::endl;
            }
            return ss;
        }

        unsigned char &operator()(size_t r, size_t c)
        {
            return matrix[c + r * width];
        };

        void clear()
        {
            std::fill(matrix.begin(), matrix.end(), 0);
        }

    private:
        size_t width;
        size_t height;

        unsigned char val_to_char(unsigned char i)
        {
            switch (i >> 5)
            {
            case 0:
                return ' ';
            case 1:
                return '.';
            case 2:
                return '-';
            case 3:
                return ':';
            case 4:
                return '|';
            case 5:
                return '9';
            case 6:
                return '8';
            case 7:
                return '@';
            default:
                return ' ';
            }
        }

        std::vector<unsigned char> matrix;
    };

}

#endif