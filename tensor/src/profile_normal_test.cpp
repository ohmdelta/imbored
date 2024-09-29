#include <chrono>

#include <omp.h>

// #define BLOCK_SIZE 64
#include "tensor.hpp"
using namespace tensor;

int main()
{
    Matrix<int> A(1024, 1024, 0);
    Matrix<int> B(1024, 1024, 0);
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
            if (c.matrix_[i] != 1048577)
            {
                std::cout << "Error: " << i << ", " << c.matrix_[i] << std::endl;
            }
        }
    }

    {
        const auto LEN = 1024 * 1024;
        const auto K = 1024;
        int *a = (int *)malloc(LEN * sizeof(int)), *b = (int *)malloc(LEN * sizeof(int)), *c = (int *)malloc(LEN * sizeof(int));
        for (size_t i = 0; i < LEN; i++)
        {
            a[i] = i + 1;
            b[i] = LEN - i;
        }
        auto start = std::chrono::system_clock::now();
        for (size_t n = 0; n < 10; n++)
        {
            for (size_t k = 0; k < K; k++)
            {
                for (size_t i = 0; i < LEN / BLOCK_SIZE / K; i++)
                {
                    size_t ind = i * BLOCK_SIZE + K * k;
#pragma omp simd
                    for (size_t j = 0; j < BLOCK_SIZE; j++)
                    {
                        size_t idx = ind + j;
                        c[idx] = a[idx] + b[idx];
                    }
                }
            }
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Elapsed time: " << elapsed_seconds.count() << std::endl;
        for (size_t i = 0; i < LEN; i++)
        {
            if (c[i] != LEN + 1)
            {
                std::cout << "Error: " << i << ", " << c[i] << std::endl;
            }
        }
        free(a);
        free(b);
        free(c);
        a = nullptr;
        b = nullptr;
        c = nullptr;
    }

    {
        const auto LEN = 4;
        int *a = (int *)malloc(LEN * sizeof(int)), *b = (int *)malloc(LEN * sizeof(int));
        for (size_t i = 0; i < LEN; i++)
        {
            a[i] = (1 << 10) + i + 1;
            b[i] = (1 << 10) + LEN - i;
        }
        auto start = std::chrono::system_clock::now();
        for (size_t n = 0; n < 1000000; n++)
        {
            int *c = (int *)malloc(LEN * sizeof(int));
#pragma omp simd
            for (size_t idx = 0; idx < LEN; idx++)
            {
                c[idx] = a[idx] + b[idx];
            }
#pragma omp simd
            for (size_t i = 0; i < LEN; i++)
            {
                if (c[i] != (1 << 11) + LEN + 1)
                {
                    std::cout << "Error: " << i << ", " << c[i] << std::endl;
                }
            }
            free(c);
            c = nullptr;
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Elapsed time: " << elapsed_seconds.count() << std::endl;
        free(a);
        free(b);
        a = nullptr;
        b = nullptr;
    }

    {
        const size_t LEN = 1<<20;
        std::cout << "Malloc test: ";
        auto start = std::chrono::system_clock::now();
        for (size_t n = 0; n < 1000000; n++)
        {
            int *c = (int *)(LEN * sizeof(int));
            std::fill(c, c + LEN, 10);
            free(c);
            c = nullptr;
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Elapsed time: " << elapsed_seconds.count() << std::endl;
    }

    return 0;
}
