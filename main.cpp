#include <iostream>
#include "lin_alg/coordinate.hpp"

using namespace lin_alg;

int main()
{
    auto coord = lin_alg::Coordinate(1.0, 2.0, 3.0);
    std::cout << coord[0] << std::endl;
    std::cout << coord[2] << std::endl;
    std::cout << coord.a << std::endl;
    auto coord2 = coord * coord;
    std::cout << coord2 << std::endl;

    auto coord3 = coord + coord;
    std::cout << coord3 << std::endl;
    auto coord4 = coord * 4.5;
    std::cout << coord4 << std::endl;
    coord4[2] = 5;
    std::cout << coord4 << std::endl;

    std::cout << "Hello" << std::endl;
}