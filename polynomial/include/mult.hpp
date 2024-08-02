#ifndef MULT_HPP
#define MULT_HPP

namespace polynomial
{

    const double EPSILON = 1e-7;

    inline double sq(double x) { return x * x; }
    inline double cube(double x) { return x * x * x; }
    inline double supercube(double x) { return sq(x) * sq(x); }
};

#endif