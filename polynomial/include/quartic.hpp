#ifndef QUARTIC_HPP
#define QUARTIC_HPP

#include <cstdint>
#include <cmath>
#include <algorithm>

namespace polynomial
{

    inline double sq(double x) { return x * x; }
    inline double cube(double x) { return x * x * x; }
    inline double supercube(double x) { return sq(x) * sq(x); }

    inline double D(double a, double e, double c, double b, double d)
    {
        return 64 * cube(a) * e - 16 * sq(a) * sq(c) + 16 * a * sq(b) * c - 16 * sq(a) * b * d - 3 * supercube(b);
    }

    inline double P(double a, double c, double b)
    {
        return 8 * a * c - 3 * sq(b);
    }

    inline double sol_1_b(double b, double a, double S)
    {
        return -b / (4 * a) - S;
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

    QuarticSolution solve_quartic(
        double a,
        double b,
        double c,
        double d,
        double e)
    {

        QuarticSolution solution;

        double p = (8 * a * c - 3 * sq(b)) / (8 * sq(a));
        double q = (cube(b) - 4 * a * b * c + 8 * sq(a) * d) / (8 * cube(a));

        double delta0 = sq(2) - 3 * b * d + 12 * a * e;
        double delta1 = 2 * cube(c) - 9 * b * c * d + 27 * sq(b) * e + 27 * a * sq(d) - 72 * a * c * e;

        double u = sq(delta1) - 4 * cube(delta0);

        double det = -u;

        if (det > 0)
        {
            double Q = std::cbrt((delta1 + std::sqrt(det)) / 2);
            double S = std::sqrt(-2 * p / 3 + (Q + delta0 / Q) / (3 * a));

            double det1 = q / S - 2 * p - 4 * sq(S);
            double det2 = -q / S - 2 * p - 4 * sq(S);

            if (det1 == 0)
            {
                solution.add_sol(polynomial::sol_1_b(b, a, S));
            }
            else if (det1 > 0)
            {
                solution.add_sol(polynomial::sol_1_b(b, a, S) - std::sqrt(det1));
                solution.add_sol(polynomial::sol_1_b(b, a, S) + std::sqrt(det1));
            }
        }

        return solution;
    };

};

#endif