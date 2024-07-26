#ifndef QUADRATIC_HPP
#define QUADRATIC_HPP

#include <cstdint>

namespace polynomial
{
    struct Quadratic
    {
        uint8_t num_solutions;
        double sol_1;
        double sol_2;
    };

}

#endif