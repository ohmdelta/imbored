#ifndef CUBIC_HPP
#define CUBIC_HPP

#include <cstdint>
#include <cmath>
#include <algorithm>

#include "mult.hpp"

namespace polynomial
{
    struct CubicSolution
    {
    private:
        const static size_t MAX_SOLUTIONS = 3;
        typedef double *iterator;
        typedef const double *const_iterator;

    public:
        uint8_t num_solutions = 0;
        double sol[MAX_SOLUTIONS] = {};

        void add_sol(double v)
        {
            if (num_solutions < MAX_SOLUTIONS)
            {
                sol[num_solutions++] = v;
            }
        }

        double min()
        {
            return *std::min_element(sol, sol + num_solutions);
        }

        bool in(double value)
        {
            auto v = std::find(sol, sol + num_solutions, value);
            return v == (sol + num_solutions);
        }

        iterator begin() { return sol; }
        const_iterator begin() const { return sol; }
        iterator end() { return sol + num_solutions; }
        const_iterator end() const { return sol + num_solutions; }
    };

    CubicSolution solve_cubic(double a, double b, double c, double d);
    CubicSolution solve_depressed_cubic(double p, double q);

    constexpr double M_2_PI_3();

}

#endif