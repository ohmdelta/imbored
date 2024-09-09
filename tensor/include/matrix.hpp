#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <type_traits>
#include <concepts>
#include <cstddef>
#include <stdexcept>
#include <ostream>
#include <iostream>

namespace tensor
{

    template <typename T>
    concept Arithmetic = std::integral<T> or std::floating_point<T>;

    template <Arithmetic T>
    class Matrix
    {
    public:
        size_t rows_, columns_;
        T *matrix_;

    public:
        Matrix(size_t rows, size_t columns) : rows_(rows), columns_(columns)
        {
            matrix_ = new T[rows_ * columns_]{0};
        }

        Matrix(const Matrix<T> &m) : rows_(m.rows_), columns_(m.columns_)
        {
            size_t size = rows_ * columns_;
            this->matrix_ = new T[size];

            memcpy(matrix_, m.matrix_, size * sizeof(T));
        }

        ~Matrix()
        {
            delete[] matrix_;
        }

        T &operator()(size_t r, size_t c)
        {
            if (r < rows_ && c < columns_)
                return matrix_[r * rows_ + c];
            else
            {
                throw std::invalid_argument("Requested index for row or column column invalid!");
            }
        }

        const T &operator()(size_t r, size_t c) const
        {
            if (r < rows_ && c < columns_)
                return matrix_[r * rows_ + c];
            else
            {
                throw std::invalid_argument("Requested index for row or column column invalid!");
            }
        }

        template <Arithmetic S>
        auto operator*(const Matrix<S> &v) -> Matrix<decltype(operator()(0, 0) * v(0, 0))>
        {
            if (columns_ == v.rows_)
            {
                Matrix<decltype(operator()(0, 0) * v(0, 0))>
                    m(rows_, v.columns_);

                for (size_t i = 0; i < rows_; i++)
                {
                    for (size_t j = 0; j < v.columns_; j++)
                    {
                        for (size_t k = 0; k < columns_; k++)
                        {
                            m(i, j) += operator()(i, k) * v(k, j);
                        }
                    }
                }
                return m;
            }
            else
            {
                throw std::invalid_argument("Cannot multiply matrices - dimension mismatch");
            }
        }

        template <Arithmetic S>
        auto operator+(const Matrix<S> &v) -> Matrix<decltype(operator()(0, 0) + v(0, 0))>
        {
            if (columns_ == v.columns_ && rows_ == v.rows_)
            {
                Matrix<decltype(operator()(0, 0) * v(0, 0))>
                    m(rows_, columns_);

                for (size_t i = 0; i < rows_; i++)
                {
                    for (size_t j = 0; j < v.columns_; j++)
                    {
                        m(i, j) = operator()(i, j) + v(i, j);
                    }
                }
                return m;
            }
            else
            {
                throw std::invalid_argument("Cannot multiply matrices - dimension mismatch");
            }
        }
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Matrix<T> &s)
    {
        for (size_t i = 0; i < s.rows_; i++)
        {
            for (size_t j = 0; j < s.columns_; j++)
            {
                os << s(i, j) << " ";
            }
            os << "\n";
        }

        return os;
    }

};

#endif