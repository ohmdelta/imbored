#include "cubic.hpp"
#include <iostream>

namespace polynomial
{
    CubicSolution solve_depressed_cubic(double p, double q)
    {
        CubicSolution solution;
        if (p == 0 && q == 0)
        {
            solution.add_sol(0);
            return solution;
        }

        double v = sq(q) / 4 + cube(p) / 27;
        // std::cout << "V" << v << std::endl;
        if (v == 0)
        {
            solution.add_sol(3 * q / p);
            solution.add_sol(-3 * q / (2 * p));
            solution.add_sol(-3 * q / (2 * p));
        }
        else if (v > 0)
        {
            double u1 = -q / 2 + std::sqrt(v);
            double u2 = -q / 2 - std::sqrt(v);

            solution.add_sol(std::cbrt(u1) + std::cbrt(u2));
        }
        else
        {
            if (p < 0)
            {
                double u = std::acos(3 * q / (2 * p) * std::sqrt(-3 / p)) / 3;

                for (size_t i = 0; i < 3; i++)
                {
                    solution.add_sol(2 * std::sqrt(-p / 3) * std::cos(u - 2 * M_PI / 3 * i));
                }
            }
        }

        return solution;
    }

    CubicSolution solve_cubic(double a, double b, double c, double d)
    {
        double p = (3 * a * c - sq(b)) / (3 * sq(a));
        double q = (2 * cube(b) - 9 * a * b * c + 27 * sq(a) * d) / (27 * cube(a));
        double offset = b / (3 * a);

        // std::cout << p << ", " << q << ", " << offset << std::endl;
        auto sol = solve_depressed_cubic(p, q);
        for (size_t i = 0; i < sol.num_solutions; i++)
        {
            sol.sol[i] -= offset;
        }

        return sol;

        /*
        CubicSolution solution;

        double delta0 = sq(b) - 3 * a * c;
        double delta1 = 2 * cube(b) - 9 * a * b * c + 27 * sq(a) * d;

        double C1 = std::cbrt((delta1 + std::sqrt(sq(delta1) - 4 * cube(delta0))) / 2);
        double C2 = std::cbrt((delta1 - std::sqrt(sq(delta1) - 4 * cube(delta0))) / 2);

        if (C1 && C2)
        {
            double x = -b / (3 * a);
            solution.add_sol(x);
        }
        else
        {
            double C = C1 == 0 ? C2 : C1;
            double x = -(b + C + delta0 / C);
            solution.add_sol(x);
        }
        return solution;
        */
    }
}
