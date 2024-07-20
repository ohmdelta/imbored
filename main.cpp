#include <iostream>
#include "lin_alg/coordinate.hpp"

int main()
{
    auto coord = lin_alg::Coordinate(1.0,2.0,3.0);
    std::cout << coord[0] << std::endl;
    std::cout << coord[2] << std::endl;
    std::cout << coord.a << std::endl;
    auto coord2 = coord * coord;
    std::cout << coord2 << std::endl;

    std::cout << "Hello" << std::endl;
}