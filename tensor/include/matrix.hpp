#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <type_traits>
#include <concepts>
#include <cstddef>
#include <stdexcept>
#include <ostream>
#include <iostream>
#include <memory>
#include <bit>

namespace tensor
{

    template <typename T>
    concept Arithmetic = std::integral<T> or std::floating_point<T>;

    template <Arithmetic T>
    class SlicedMatrix;

    template <Arithmetic T>
    struct IMatrix
    {

        virtual T &operator()(size_t r, size_t c) = 0;
        virtual const T &operator()(size_t r, size_t c) const = 0;
    };

    template <Arithmetic T>
    class Matrix : public IMatrix<T>
    {
    public:
        size_t rows_, columns_;
        size_t len_ = rows_ * columns_;
        bool transposed_ = false;
        T *matrix_ = nullptr;

    public:
        Matrix(size_t rows, size_t columns) : rows_(rows), columns_(columns)
        {
            matrix_ = new T[len_]{0};
        }

        Matrix(const Matrix<T> &m) : rows_(m.rows_), columns_(m.columns_), transposed_(m.transposed_)
        {
            this->matrix_ = new T[len_];
            memcpy(matrix_, m.matrix_, len_ * sizeof(T));
        }

        ~Matrix()
        {
            delete[] matrix_;
            matrix_ = nullptr;
        }

        T &operator()(size_t r, size_t c) override
        {
            if (r < rows_ && c < columns_)
            {
                if (transposed_)
                    return matrix_[r + c * rows_];
                return matrix_[r * columns_ + c];
            }
            else
            {
                throw std::invalid_argument("Requested index for row or column invalid!");
            }
        }

        const T &operator()(size_t r, size_t c) const override
        {
            if (r < rows_ && c < columns_)
            {
                if (transposed_)
                    return matrix_[r + c * rows_];
                return matrix_[r * columns_ + c];
            }
            else
            {
                throw std::invalid_argument("Requested index for row or column invalid!");
            }
        }

        // START: MATRIX - MATRIX Operations
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
        auto strassen_multiplication(const Matrix<S> &v) -> Matrix<decltype(operator()(0, 0) * v(0, 0))>
        {
            using MT = decltype(operator()(0, 0) * v(0, 0));
            if (columns_ == v.rows_ && rows_ == v.columns_ == columns_ && !(rows_ & (rows_ - 1)))
            {
                Matrix<MT>
                    m(rows_, v.columns_);

                size_t k = columns_;
                for (size_t i = 2; i < columns_; i <<= 1)
                {
                    size_t sub_mat_size = i >> 1;
                    for (size_t j = 0; j < columns_; j++)
                    {
                    }
                }

                return m;
            }
            else
            {
                throw std::invalid_argument("Strassen Multiplication: needs square matrices atm");
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
        // END: MATRIX - MATRIX Operations

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
        auto operator-(S c) -> Matrix<decltype(operator()(0, 0) + c)>
        {
            return operator+(-c);
        }

        template <Arithmetic S>
        Matrix<T> operator-()
        {
            return operator*(-1);
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

        void transpose_inplace()
        {
            transposed_ ^= true;
            std::swap(rows_, columns_);
        }

        Matrix<T> transpose() const
        {
            Matrix<T> transpose = *this;
            transpose.transpose_inplace();

            return transpose;
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

    template <Arithmetic T>
    class SlicedMatrix : public IMatrix<T>
    {
    private:
        std::shared_ptr<Matrix<T>> matrix;

        // start inclusive, end exclusive;
        size_t row_start = 0, row_end = 0, column_start = 0, column_end = 0;

    public:
        size_t rows_ = row_end - row_start;
        size_t columns_ = column_end - column_start;

    public:
        SlicedMatrix(
            std::shared_ptr<Matrix<T>> mat,
            size_t row_end_,
            size_t column_end_) : matrix(mat),
                                  row_end(row_end_), column_end(column_end_)
        {
            if (row_end_ >= mat->rows_ || column_end_ >= mat->columns_)
            {
                throw std::invalid_argument("Could not init sliced matrix because dimensions given.");
            }
        }

        SlicedMatrix(
            std::shared_ptr<Matrix<T>> mat,
            size_t row_start_,
            size_t row_end_,
            size_t column_start_,
            size_t column_end_) : matrix(mat),
                                  row_start(row_start_),
                                  row_end(row_end_),
                                  column_start(column_start_),
                                  column_end(column_end_)
        {
            if (row_end_ >= mat->rows_ || column_end_ >= mat->columns_)
            {
                throw std::invalid_argument("Could not init sliced matrix because dimensions given.");
            }
        }

        inline T &operator()(size_t r, size_t c) override
        {
            return (*matrix)(r + row_start, c + column_start);
        }

        inline const T &operator()(size_t r, size_t c) const override
        {
            return matrix->operator()(r + row_start, c + column_start);
        }

        template <Arithmetic S>
        auto operator*(const SlicedMatrix<S> &v) -> Matrix<decltype(operator()(0, 0) * v(0, 0))>
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
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const SlicedMatrix<T> &s)
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
    };

};

#endif