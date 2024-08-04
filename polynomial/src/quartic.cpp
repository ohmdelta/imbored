#include "quartic.hpp"
#include "cubic.hpp"
#include "quadratic.hpp"

namespace polynomial
{
    double P(double a, double b, double c)
    {
        return (8 * a * c - 3 * sq(b)) / (8 * sq(a));
    };

    double Q(double a, double b, double c, double d)
    {
        return (cube(b) - 4 * a * b * c + 8 * sq(a) * d) / (8 * cube(a));
    }

    QuarticSolution solve_depressed_quartic(
        double p,
        double q,
        double r)
    {
        if (std::abs(q) < EPSILON)
        {
            QuadraticSolution quadraticSolution = solve_quadratic(1, p, r);
            QuarticSolution solution;

            for (const auto &i : quadraticSolution)
            {
                if (i >= 0)
                {
                    double v = std::sqrt(i);
                    solution.add_sol(-v);
                    solution.add_sol(v);
                }
            }

            return solution;
        }

        CubicSolution cubicSol = solve_cubic(8, 8 * p, (2 * sq(p) - 8 * r), -sq(q));
        if (cubicSol.num_solutions == 0)
        {
            return QuarticSolution();
        }
        else
        {
            QuarticSolution solution;

            // double m = std::find_first_of(std::begin(cubicSol.sol), std::end(cubicSol), );
            for (auto &m : cubicSol)
            {
                if (m <= 0)
                    continue;

                // Solve y**2 +- sqrt(2m) y + p/2 + m -+ q/(2sqrt(2m))
                double sqrt_m = std::sqrt(m);
                double det_pos = -(2 * p + 2 * m + M_SQRT2 * q / sqrt_m);
                double det_neg = -(2 * p + 2 * m - M_SQRT2 * q / sqrt_m);

                if (det_pos < 0 && det_neg < 0)
                    continue;

                double sqrt_2m = sqrt_m * M_SQRT2;

                if (det_pos > 0)
                {
                    solution.add_sol((sqrt_2m + std::sqrt(det_pos)) / 2);
                    solution.add_sol((sqrt_2m - std::sqrt(det_pos)) / 2);
                }

                if (det_neg > 0)
                {
                    solution.add_sol((-sqrt_2m + std::sqrt(det_neg)) / 2);
                    solution.add_sol((-sqrt_2m - std::sqrt(det_neg)) / 2);
                }

                break;
            }

            return solution;
        }
    }

    QuarticSolution solve_quartic(
        double a,
        double b,
        double c,
        double d,
        double e)
    {
        // QuarticSolution solution;
        double b_ = b / a;
        double c_ = c / a;
        double d_ = d / a;
        double e_ = e / a;
        double offset = b_ / 4;

        double p = c_ - 3 * sq(b_) / 8;
        double q = (cube(b_) - 4 * b_ * c_ + 8 * d_) / 8;
        double r = (-3 * supercube(b_) + 256 * e_ - 64 * b_ * d_ + 16 * sq(b_) * c_) / 256;

        auto solution = solve_depressed_quartic(p, q, r);

        for (auto &&i : solution)
        {
            i -= offset;
        }

        return solution;
    }

}
