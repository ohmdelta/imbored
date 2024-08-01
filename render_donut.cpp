#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <memory>
#include <unistd.h>
#include <thread>

#include "renderer.hpp"
#include "lin_alg.hpp"

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

TransformationMatrix set_transformation_angle_y(TransformationMatrix transformation, double angle)
{
    transformation(1, 1) = std::cos(angle);
    transformation(1, 2) = -std::sin(angle);
    transformation(2, 1) = std::sin(angle);
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
    std::shared_ptr<TerminalDisplay> t = std::make_shared<TerminalDisplay>(cols, rows, 2);

    // auto z = 50;
    auto sphere = std::make_shared<Torus>(
        40,
        80);

    auto sphere2 = std::make_shared<Torus>(
        40,
        80);

    // auto y = -50;
    TransformationMatrix transformation = Identity();
    TransformationMatrix transformation2 = Identity();
    double angle_ = M_PI_2;
    transformation2(0, 0) = std::cos(angle_);
    transformation2(0, 1) = -std::sin(angle_);
    transformation2(1, 0) = std::sin(angle_);
    transformation2(1, 1) = std::cos(angle_);

    TransformationMatrix transformation3 = Identity();
    transformation3(1, 1) = std::cos(angle_);
    transformation3(1, 2) = -std::sin(angle_);
    transformation3(2, 1) = std::sin(angle_);
    transformation3(2, 2) = std::cos(angle_);

    transformation2 = transformation3 * transformation2;

    auto angle = 0.0;

    auto plane = std::make_shared<CheckerBoard>(
        lin_alg::Coordinate(0, 100, 0),
        lin_alg::Coordinate(0, 1, 0),
        lin_alg::Coordinate(0.01, 0, 0));

    world.add_object(plane);

    world.add_object(sphere);
    world.add_object(sphere2);
    sphere->set_origin(Coordinate(2500, -160, 0));
    sphere2->set_origin(Coordinate(2500, -160, 240));

    for (size_t i = 0; i < 210; i++)
    {
        t->clear();
        world.render_perspective(t);
        std::cout << t->render_to_str().str();
        // current = transformation * current;
        transformation = set_transformation_angle_z(transformation, angle);
        sphere->set_rotation(transformation);
        sphere2->set_rotation(transformation * transformation2);
        // std::cout << transformation << std::endl;
        angle += M_PI_2 / 32;
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }

    return 0; // make sure your main returns int
}
