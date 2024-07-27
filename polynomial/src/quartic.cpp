#include "quartic.hpp"

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
