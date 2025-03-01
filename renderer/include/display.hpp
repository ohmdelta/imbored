#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <vector>
#include <cassert>
#include <ostream>
#include <cmath>
#include <sstream>

namespace renderer
{
    struct StringBuffer
    {
        StringBuffer(size_t width, size_t height) : width(width), height(height), size(height * width)
        {
            s = new char[size];
        }

        size_t width, height, size;


        ~StringBuffer()
        {
            delete[] s;
        }

        char *s;
    };

    struct Display
    {
        virtual size_t width() = 0;
        virtual size_t height() = 0;

        virtual unsigned char &operator()(size_t r, size_t c) = 0;
    };

    class TerminalDisplay : public Display
    {
    public:
        TerminalDisplay(
            size_t width__,
            size_t height__,
            size_t char_per_pixel = 1) : width_(width__ / char_per_pixel),
                                         height_(height__),
                                         char_per_pixel_(char_per_pixel),
                                         matrix(width_ * height_, 0)
        {
        }

        void resize(size_t width_, size_t height_);

        std::stringstream render_to_str();
        StringBuffer render_to_c_str();

        unsigned char &operator()(size_t r, size_t c);

        void clear();

        size_t width()
        {
            return width_;
        }

        size_t height()
        {
            return height_;
        }

    private:
        size_t width_;
        size_t height_;

        size_t char_per_pixel_;
        
        unsigned char val_to_char_3_bit(unsigned char i);
        unsigned char val_to_char_4_bit(unsigned char i);

        std::vector<unsigned char> matrix;
    };

}

#endif