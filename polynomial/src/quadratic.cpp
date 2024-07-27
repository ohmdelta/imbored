#include "quadratic.hpp"

namespace polynomial
{
    QuadraticSolution solve_quadratic(double a, double b, double c)
    {
        QuadraticSolution sol;

        auto det = sq(b) - 4 * a * c;
        if (det < 0)
        {
            return sol;
        }
        else if (det == 0)
        {
            sol.add_sol(-b / (2 * a));
        } else {
            sol.add_sol((-b - std::sqrt(det))/ (2 * a));
            sol.add_sol((-b + std::sqrt(det))/ (2 * a));
        }

        return sol;
    }

} // namespace polynomial
