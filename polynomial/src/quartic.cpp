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
        if (q == 0)
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
        QuarticSolution solution;

        double p_ = P(a, b, c);
        double q_ = Q(a, b, c, d);
        std::cout << "p, q" << p_ << " " << q_ << std::endl;
        double delta0 = sq(c) - 3 * b * d + 12 * a * e;
        double delta1 = 2 * cube(c) - 9 * b * c * d + 27 * sq(b) * e + 27 * a * sq(d) - 72 * a * c * e;

        double u = sq(delta1) - 4 * cube(delta0);
        std::cout << "U: " << u << std::endl;

        double det = -u;

        if (u > 0)
        {
            std::cout << "DET > 0 " << u << std::endl;
            double Q_ = std::cbrt((delta1 + std::sqrt(u)) / 2);

            double S_ = std::sqrt(-2 * p_ / 3 + (Q_ + delta0 / Q_) / (3 * a));

            std::cout << "Q_ " << Q_ << " S_ " << S_ << " p_ " << p_ << std::endl;

            double det1 = q_ / S_ - 2 * p_ - 4 * sq(S_);
            double det2 = -q_ / S_ - 2 * p_ - 4 * sq(S_);

            // if (abs(det1) < 1e-9)
            // {
            //     det1 = 0;
            // }

            // if (abs(det2) < 1e-9)
            // {
            //     det2 = 0;
            // }

            // std::cout << "DET 1 " << det1 << std::endl;
            // std::cout << "DET 2 " << det2 << std::endl;

            if (det1 == 0)
            {
                solution.add_sol(polynomial::sol_1_b(b, a, S_));
            }
            else if (det1 > 0)
            {
                solution.add_sol(polynomial::sol_1_b(b, a, S_) - std::sqrt(det1));
                solution.add_sol(polynomial::sol_1_b(b, a, S_) + std::sqrt(det1));
            }

            if (det2 == 0)
            {
                solution.add_sol(polynomial::sol_2_b(b, a, S_));
            }
            else if (det2 > 0)
            {
                solution.add_sol(polynomial::sol_2_b(b, a, S_) - std::sqrt(det2));
                solution.add_sol(polynomial::sol_2_b(b, a, S_) + std::sqrt(det2));
            }
        }
        else if (u < 0)
        {
            std::cout << "DET < 0 " << det << " " << delta0 << std::endl;
            double phi = std::acos(delta1 / (2 * sqrt(cube(delta0))));
            double S2_ = (-2 * p_ / 3) + 2 / (3 * a) * sqrt(delta0) * std::cos(phi / 3);
            double S_ = std::sqrt(S2_) / 2;
            std::cout << "S_ " << S_ << " S2_ " << S2_ << " q " << q_ << " p " << p_ << std::endl;

            double det1 = q_ / S_ - 2 * p_ - 4 * sq(S_);
            double det2 = -q_ / S_ - 2 * p_ - 4 * sq(S_);

            std::cout << "1" << det1 << std::endl;
            if (det1 == 0)
            {
                solution.add_sol(polynomial::sol_1_b(b, a, S_));
            }
            else if (det1 > 0)
            {
                solution.add_sol(polynomial::sol_1_b(b, a, S_) - std::sqrt(det1));
                solution.add_sol(polynomial::sol_1_b(b, a, S_) + std::sqrt(det1));
            }

            std::cout << "2" << det2 << std::endl;

            if (det2 == 0)
            {
                solution.add_sol(polynomial::sol_2_b(b, a, S_));
            }
            else if (det2 > 0)
            {
                solution.add_sol(polynomial::sol_2_b(b, a, S_) - std::sqrt(det2));
                solution.add_sol(polynomial::sol_2_b(b, a, S_) + std::sqrt(det2));
            }
        }
        return solution;
    }

}
