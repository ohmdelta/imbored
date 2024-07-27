#ifndef MULT_HPP
#define MULT_HPP

namespace polynomial
{
    inline double sq(double x) { return x * x; }
    inline double cube(double x) { return x * x * x; }
    inline double supercube(double x) { return sq(x) * sq(x); }
};

#endif