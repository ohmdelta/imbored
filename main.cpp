#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "renderer/renderer.hpp"
#include "lin_alg/lin_alg.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace lin_alg;
using namespace renderer;

int main(int argc, char **argv)
{
    auto coord = lin_alg::Vector(1.0, 2.0, 3.0);
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
    TransformationMatrix v = ident / 10;

    std::cout << v << std::endl;
    std::cout << ident << std::endl;

    ident(2, 0) = 2;
    std::cout << ident << std::endl;

    ident.transpose();
    std::cout << ident << std::endl;
    ident.transpose();
    std::cout << ident << std::endl;
    {
        auto coord = lin_alg::Coordinate(1.0, 2.0, 3.0, 2.0);
        std::cout << coord << std::endl;
    }

    for (size_t i = 0; i < 8; i++)
    {
        std::cout << ((32 * i + 1) >> 5) << std::endl;
    }

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    size_t rows = w.ws_row - 1;
    size_t cols = w.ws_col - 1;
    std::cout << "lines " << rows << std::endl;
    std::cout << "columns " << cols << std::endl;

    renderer::TerminalRenderer t(cols, rows);

    cv::VideoCapture cap("./videoplayback.mp4");
    if (!cap.isOpened()) // check if we succeeded
        return 1;

    cv::Mat frame;

    while (cap.read(frame))
    {
        cv::Mat temp_;
        cv::cvtColor(frame, temp_, cv::COLOR_BGR2GRAY);

        cv::Mat temp;
        cv::resize(temp_, temp, cv::Size(cols, rows), 0, 0, cv::INTER_AREA);

        auto s = temp.size;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                t(i, j) = temp.at<unsigned char>(i, j);
            }
        }
        std::cout << t.render_to_str().str();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        t.clear();
    }

    return 0; // make sure your main returns int
}