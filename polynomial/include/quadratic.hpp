#ifndef QUADRATIC_HPP
#define QUADRATIC_HPP

#include <cstdint>
#include <cmath>
#include <algorithm>

#include "mult.hpp"

namespace polynomial
{
    struct QuadraticSolution
    {

    private:
        const static size_t MAX_SOLUTIONS = 2;
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

        iterator begin() { return sol; }
        const_iterator begin() const { return sol; }
        iterator end() { return sol + num_solutions; }
        const_iterator end() const { return sol + num_solutions; }
    };

    QuadraticSolution solve_quadratic(double a, double b, double c);

}

#endif