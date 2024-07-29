#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <memory>
#include <unistd.h>
#include <thread>

#include "renderer.hpp"
#include "lin_alg/lin_alg.hpp"

using namespace lin_alg;
using namespace renderer;

TransformationMatrix set_transformation_angle_z(TransformationMatrix transformation, double angle)
{
    transformation(0, 0) = std::cos(angle);
    transformation(0, 2) = -std::sin(angle);
    transformation(2, 0) = std::sin(angle);
    transformation(2, 2) = std::cos(angle);
    return transformation;
}

int main()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    size_t rows = w.ws_row - 1;
    size_t cols = w.ws_col - 1;
    std::cout << "lines " << rows << std::endl;
    std::cout << "columns " << cols << std::endl;

    World world(cols, rows, 3, 500);
    TerminalDisplay t(cols, rows, 2);

    // auto z = 50;
    auto sphere = std::make_shared<Torus>(
        40,
        80);

    // auto y = -50;
    TransformationMatrix transformation = Identity();
    auto angle = 0.0;

    world.add_object(sphere);
    sphere->set_origin(Coordinate(2500, 0, 0));

    for (size_t i = 0; i < 210; i++)
    {
        t.clear();
        world.render_perspective(t);
        std::cout << t.render_to_str().str();
        // current = transformation * current;
        transformation = set_transformation_angle_z(transformation, angle);
        sphere->set_rotation(transformation);
        // std::cout << transformation << std::endl;
        angle += M_PI_2 / 32;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    return 0; // make sure your main returns int
}
