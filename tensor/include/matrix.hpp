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
        size_t len_ = rows_ * columns_;
        T *matrix_;

    public:
        Matrix(size_t rows, size_t columns) : rows_(rows), columns_(columns)
        {
            matrix_ = new T[len_]{0};
        }

        Matrix(const Matrix<T> &m) : rows_(m.rows_), columns_(m.columns_)
        {
            this->matrix_ = new T[len_];
            memcpy(matrix_, m.matrix_, len_ * sizeof(T));
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
            if (len_ == v.len_ && columns_ == v.columns_)
            {
                Matrix<decltype(operator()(0, 0) + v(0, 0))>
                    m(rows_, columns_);

                for (size_t i = 0; i < len_; i++)
                {
                    m.matrix_[i] = matrix_[i] + v.matrix_[i];
                }
                return m;
            }
            else
            {
                throw std::invalid_argument("Cannot multiply matrices - dimension mismatch");
            }
        }

        template <Arithmetic S>
        auto operator*(S c) -> Matrix<decltype(operator()(0, 0) * c)>
        {
            Matrix<decltype(operator()(0, 0) * c)>
                m(rows_, columns_);

            for (size_t i = 0; i < len_; i++)
            {
                m.matrix_[i] = matrix_[i] * c;
            }
            return m;
        }

        template <Arithmetic S>
        auto operator+(S c) -> Matrix<decltype(operator()(0, 0) + c)>
        {
            Matrix<decltype(operator()(0, 0) + c)>
                m(rows_, columns_);

            for (size_t i = 0; i < len_; i++)
            {
                m.matrix_[i] = matrix_[i] + c;
            }
            return m;
        }

        template <Arithmetic S>
        void operator+=(S c) 
        {
            for (size_t i = 0; i < len_; i++)
            {
                matrix_[i] += c;
            }
        }

        template <Arithmetic S>
        void operator*=(S c) 
        {
            for (size_t i = 0; i < len_; i++)
            {
                matrix_[i] *= c;
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