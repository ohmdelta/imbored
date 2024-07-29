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

    auto z= 50;
    auto sphere = std::make_shared<Sphere>(
        40,
        Coordinate(5000, 0, z));

    // auto y = -50;
    auto depth = 5000;
    auto sphere2 = std::make_shared<Sphere>(
        5,
        Coordinate(depth, 5, 0));

    world.add_object(sphere);
    world.add_object(sphere2);

    for (size_t i = 0; i < 210; i++)
    {
        t.clear();
        sphere->set_origin(Coordinate(5000, 0, ++z));
        sphere2->set_origin(Coordinate(depth, 5, 0));
        depth -= 25;
        world.render_perspective(t);
        std::cout << t.render_to_str().str();

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    return 0; // make sure your main returns int
}
