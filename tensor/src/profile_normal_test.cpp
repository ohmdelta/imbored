#include <chrono>

#include "tensor.hpp"

using namespace tensor;

int main()
{
    Matrix<long> A(1024, 1024, 0);
    Matrix<long> B(1024, 1024, 0);
    for (size_t i = 0; i < A.len_; i++)
    {
        A.matrix_[i] = i + 1;
        B.matrix_[i] = A.len_ - i;
    }

    {
        auto start = std::chrono::system_clock::now();
        auto C = A * B;
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Elapsed time: " << elapsed_seconds.count() << std::endl;
    }

    {
        auto start = std::chrono::system_clock::now();
        auto c = A.elementwise_addition(B);
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Elapsed time: " << elapsed_seconds.count() << std::endl;
        for (size_t i = 0; i < c.len_; i++)
        {
            if(c.matrix_[i] != 1048577)
            {
                std::cout << "Error: " << i << ", " << c.matrix_[i] << std::endl;
            }
        }
    }
    return 0;
}
