#include <iostream>
#include <vector>
#include <stdexcept>

#include "renderer.hpp"

namespace renderer
{
    unsigned char TerminalDisplay::val_to_char(unsigned char i)
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
            return '=';
        case 5:
            return '7';
        case 6:
            return '8';
        case 7:
            return '@';
        default:
            return ' ';
        }
    }

    void TerminalDisplay::resize(size_t width_, size_t height_)
    {
        matrix.resize(width_ * height_);
    }

    std::stringstream TerminalDisplay::render_to_str()
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

    unsigned char &TerminalDisplay::operator()(size_t r, size_t c)
    {
        return matrix[c + r * width];
    };

    void TerminalDisplay::clear()
    {
        std::fill(matrix.begin(), matrix.end(), 0);
    }

}
