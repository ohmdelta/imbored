#include <iostream>
#include "lin_alg/lin_alg.hpp"

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

    // double row[4][4]{{4,2,4,5}};
    // std::cout << "R: " << row[0][0] << " " << row[0][3] << std::endl;
    
    TransformationMatrix ident = Identity();
    std::cout << ident << std::endl;

}