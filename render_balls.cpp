#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <memory>
#include <unistd.h>
#include <thread>

#include "renderer/renderer.hpp"
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

    World world(cols, rows);
    TerminalDisplay t(cols, rows, 2);

    auto z= 40;
    auto sphere = std::make_shared<Sphere>(
        20,
        Coordinate(500, 30, z));

    auto y = 10;
    auto sphere2 = std::make_shared<Sphere>(
        5,
        Coordinate(500, y, 10));

    world.add_object(sphere);
    world.add_object(sphere2);

    for (size_t i = 0; i < 50; i++)
    {
        t.clear();
        sphere->set_origin(Coordinate(500, 30, ++z));
        sphere2->set_origin(Coordinate(500, ++y, 10));
        world.render_orthographic(t);
        std::cout << t.render_to_str().str();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0; // make sure your main returns int
}
