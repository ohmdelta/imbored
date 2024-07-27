#ifndef QUARTIC_HPP
#define QUARTIC_HPP

#include <cstdint>
#include <cmath>
#include <algorithm>
#include <iostream>

#include "mult.hpp"

namespace polynomial
{
    inline double D(double a, double e, double c, double b, double d)
    {
        return 64 * cube(a) * e - 16 * sq(a) * sq(c) + 16 * a * sq(b) * c - 16 * sq(a) * b * d - 3 * supercube(b);
    }

    inline double sol_1_b(double b, double a, double S)
    {
        return -b / (4 * a) - S;
    }

    inline double sol_2_b(double b, double a, double S)
    {
        return -b / (4 * a) + S;
    }

    struct QuarticSolution
    {
        uint8_t num_solutions = 0;
        double sol[4] = {};

        void add_sol(double v)
        {
            if (num_solutions < 4)
            {
                sol[num_solutions++] = v;
            }
        }

        double min()
        {
            return *std::min_element(sol, sol + num_solutions);
        }
    };

    double P(double a, double c, double b);

    double Q(double a, double b, double c, double d);

    QuarticSolution solve_depressed_quartic(
        double p,
        double q,
        double r);

    QuarticSolution solve_quartic(
        double a,
        double b,
        double c,
        double d,
        double e);

    double Q(double a, double b, double c, double d);

    double P(double a, double b, double c);
};

#endif