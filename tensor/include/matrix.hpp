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
#include <cstring>

// #define SIMD_ENABLED true
#if SIMD_ENABLED
#include <experimental/simd>
namespace stdx = std::experimental;
using floatv = stdx::native_simd<int>;
using doublev = stdx::rebind_simd_t<double, floatv>;
using intv = stdx::rebind_simd_t<int, floatv>;
using longv = stdx::rebind_simd_t<long, floatv>;
#endif

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 64
#endif

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
        Matrix(size_t rows, size_t columns, T init = 0) : rows_(rows), columns_(columns)
        {
            matrix_ = (T *)calloc(len_, sizeof(T));
            if (init)
            {
                std::fill(matrix_, matrix_ + len_, init);
            }
        }

        Matrix(T *matrix, size_t rows, size_t columns) : rows_(rows), columns_(columns), matrix_(matrix)
        {
            matrix = nullptr;
        }

        Matrix(const Matrix<T> &m) : rows_(m.rows_), columns_(m.columns_), transposed_(m.transposed_)
        {
            this->matrix_ = (T *)malloc(len_ * sizeof(T));
            memcpy(matrix_, m.matrix_, len_ * sizeof(T));
        }

        Matrix(Matrix<T> &&m) noexcept : rows_(std::move(m.rows_)),
                                         columns_(std::move(m.columns_)),
                                         transposed_(std::move(m.transposed_)),
                                         matrix_{m.matrix_}
        {
            m.matrix_ = nullptr;
        }

        ~Matrix()
        {
            free(matrix_);
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

        T *pointer(size_t r, size_t c)
        {
            if (r < rows_ && c < columns_)
            {
                if (transposed_)
                    return matrix_ + r + c * rows_;
                return matrix_ + r * columns_ + c;
            }
            else
            {
                throw std::invalid_argument("Requested index for row or column invalid!");
            }
        }

        inline const T *pointer(size_t r, size_t c) const
        {
            if (r < rows_ && c < columns_)
            {
                if (transposed_)
                    return matrix_ + r + c * rows_;
                return matrix_ + r * columns_ + c;
            }
            else
            {
                throw std::invalid_argument("Requested index for row or column invalid!");
            }
        }

        inline const T &operator()(size_t r, size_t c) const override
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
        auto elementwise_addition(const Matrix<S> &v) -> Matrix<decltype(operator()(0, 0) * v(0, 0))>
        {
            using MT = decltype(operator()(0, 0) * v(0, 0));
            if (columns_ == v.columns_ && rows_ == v.rows_)
            {
                Matrix<MT> m(rows_, v.columns_);
#if SIMD_ENABLED
                // using V_LEN = std::integral< constexpr (256 / sizeof(MT))>::value;
                constexpr size_t V_LEN = 256 / sizeof(MT);
                stdx::fixed_size_simd<MT, (256 / sizeof(MT))> a;
                stdx::fixed_size_simd<MT, (256 / sizeof(MT))> b;
                stdx::fixed_size_simd<MT, (256 / sizeof(MT))> c;
                for (size_t i = 0; i < len_ / V_LEN; i++)
                {
                    /* code */
                    a.copy_from(matrix_, stdx::element_aligned);
                    b.copy_from(v.matrix_, stdx::element_aligned);
                    c = (a + b);
                    // alignas(stdx::memory_alignment_v<stdx::native_simd<MT>>)
                    //     std::array<MT, (256 / sizeof(MT))>
                    //         mem = {};
                    // c.copy_to(&mem[0], stdx::element_aligned);

                    // for (int e : mem)
                    //     std::cout << e << ' ';
                    // std::cout << '\n';

                    c.copy_to(m.matrix_ + i * V_LEN, stdx::vector_aligned);
                }

#else
                for (size_t i = 0; i < len_; i++)
                {
                    m.matrix_[i] = matrix_[i] + v.matrix_[i];
                }
#endif
                return m;
            }
            else
            {
                throw std::invalid_argument("Cannot multiply matrices - dimension mismatch");
            }
        }

        auto elementwise_addition(const Matrix<T> &v) -> Matrix<decltype(operator()(0, 0) * v(0, 0))>
        {
            if (columns_ == v.columns_ && rows_ == v.rows_)
            {
                Matrix<T> m(rows_, v.columns_);
                memcpy(m.matrix_, matrix_, len_ * sizeof(T));
#if SIMD_ENABLED
                // using V_LEN = std::integral< constexpr (256 / sizeof(MT))>::value;
                constexpr size_t V_LEN = 256 / sizeof(MT);
                stdx::fixed_size_simd<MT, (256 / sizeof(MT))> a;
                stdx::fixed_size_simd<MT, (256 / sizeof(MT))> b;
                stdx::fixed_size_simd<MT, (256 / sizeof(MT))> c;
                for (size_t i = 0; i < len_ / V_LEN; i++)
                {
                    /* code */
                    a.copy_from(matrix_, stdx::element_aligned);
                    b.copy_from(v.matrix_, stdx::element_aligned);
                    c = (a + b);
                    c.copy_to(m.matrix_ + i * V_LEN, stdx::vector_aligned);
                }

#else
                for (size_t i = 0; i < len_ / BLOCK_SIZE; i++)
                {
                    size_t n = i * BLOCK_SIZE;
#pragma omp simd
                    for (size_t j = 0; j < BLOCK_SIZE; j++)
                    {
                        size_t k = n + j;
                        m.matrix_[k] += v.matrix_[k];
                    }
                }
#endif
                return m;
            }
            else
            {
                throw std::invalid_argument("Cannot multiply matrices - dimension mismatch");
            }
        }

        template <Arithmetic S>
        auto operator*(const Matrix<S> &v) -> Matrix<decltype(operator()(0, 0) * v(0, 0))>
        {
            if (columns_ == v.rows_)
            {
                Matrix<decltype(operator()(0, 0) * v(0, 0))>
                    m(rows_, v.columns_);

#pragma omp parallel for
                for (size_t i = 0; i < rows_; i++)
                {
                    for (size_t k = 0; k < columns_; k++)
                    {
                        for (size_t j = 0; j < v.columns_; j++)
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

        Matrix<T> operator*(const Matrix<T> &v)
        {
            if (columns_ == v.rows_)
            {
                T *m = (T *)calloc(len_, sizeof(T));

#pragma omp parallel for
                for (size_t i = 0; i < rows_; i++)
                {
                    for (size_t k = 0; k < columns_; k++)
                    {
                        size_t n = i + k * rows_;
#pragma omp simd
                        for (size_t j = 0; j < v.columns_; j++)
                        {
                            m[i * columns_ + j] += matrix_[n] * v(k, j);
                        }
                    }
                }
                Matrix<T> m_(m, rows_, v.columns_);
                m = nullptr;
                return m_;
            }
            else
            {
                throw std::invalid_argument("Cannot multiply matrices - dimension mismatch");
            }
        }

        template <Arithmetic S>
        auto strassen_multiplication(const Matrix<S> &v) -> Matrix<decltype(operator()(0, 0) * v(0, 0))>
        {
            SlicedMatrix<T> A(std::make_shared<Matrix<T>>(*this));
            SlicedMatrix<S> B(std::make_shared<Matrix<S>>(v));

            return A.strassen_multiplication(B);
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

        void insert_matrix(Matrix<T> const &m, size_t r, size_t c)
        {
            if (r < rows_ && c < columns_)
            {
                auto s_ = sizeof(T);
                auto r_ = std::min(m.rows_, rows_ - r);
                auto c_ = std::min(m.columns_, columns_ - c);
                for (size_t i = 0; i < r_; i++)
                {
                    memcpy(pointer(r + i, c), m.pointer(i, 0), c_ * s_);
                }
            }
        }

        template <Arithmetic S>
        auto operator*(S c) const -> Matrix<decltype(operator()(0, 0) * c)>
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

        Matrix<T> operator-() const
        {
            return operator* <T>(-1);
        }

        template <Arithmetic S>
        auto operator-(S c) -> Matrix<decltype(operator()(0, 0) + c)>
        {
            return operator+(-c);
        }

        template <Arithmetic S>
        auto operator-(const Matrix<S> &v) -> Matrix<decltype(operator()(0, 0) + v(0, 0))>
        {
            if (len_ == v.len_ && columns_ == v.columns_)
            {
                Matrix<decltype(operator()(0, 0) + v(0, 0))>
                    m(rows_, columns_);

                for (size_t i = 0; i < len_; i++)
                {
                    m.matrix_[i] = matrix_[i] - v.matrix_[i];
                }
                return m;
            }
            else
            {
                throw std::invalid_argument("Cannot multiply matrices - dimension mismatch");
            }
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

        // void _true_transpose() const
        // {
        //     std::swap(rows_, columns_);
        //     T* v = (T*) calloc(len_, sizeof(T));

        //     for (size_t i = 0; i < rows_; i++)
        //     {
        //         for (size_t j = 0; j < columns_; j++)
        //         {
        //             v[i + j] = operator()(i, j);
        //         }

        //     }
        //     free(matrix_);

        //     matrix_ = v;
        // }
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
    public:
        std::shared_ptr<Matrix<T>> matrix;

    private:
        // start inclusive, end exclusive;
        size_t row_start = 0, row_end = 0, column_start = 0, column_end = 0;

    public:
        size_t rows_ = row_end - row_start;
        size_t columns_ = column_end - column_start;

    public:
        SlicedMatrix(
            std::shared_ptr<Matrix<T>> mat) : matrix(mat),
                                              row_end(mat->rows_), column_end(mat->columns_)
        {
        }
        SlicedMatrix(
            std::shared_ptr<Matrix<T>> mat,
            size_t row_end_,
            size_t column_end_) : matrix(mat),
                                  row_end(row_end_), column_end(column_end_)
        {
            if (row_end_ > mat->rows_ || column_end_ > mat->columns_)
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
            if (row_end_ > mat->rows_ || column_end_ > mat->columns_)
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
        auto strassen_multiplication(const SlicedMatrix<S> &v) -> Matrix<decltype(operator()(0, 0) * v(0, 0))>
        {
            using MT = decltype(operator()(0, 0) * v(0, 0));
            if (columns_ == v.rows_ && rows_ == v.columns_ && v.columns_ == columns_ && !(rows_ & (rows_ - 1)))
            {
                Matrix<MT>
                    m(rows_, v.columns_);

                if (columns_ == 2)
                {
                    const auto a11 = (*this)(0, 0);
                    const auto a12 = (*this)(0, 1);
                    const auto a21 = (*this)(1, 0);
                    const auto a22 = (*this)(1, 1);

                    const auto b11 = v(0, 0);
                    const auto b12 = v(0, 1);
                    const auto b21 = v(1, 0);
                    const auto b22 = v(1, 1);

                    auto I = (a11 + a22) * (b11 + b22);
                    auto II = (a21 + a22) * b11;
                    auto III = a11 * (b12 - b22);
                    auto IV = a22 * (b21 - b11);
                    auto V = (a11 + a12) * b22;
                    auto VI = (a21 - a11) * (b11 + b12);
                    auto VII = (a12 - a22) * (b21 + b22);

                    m(0, 0) = I + IV - V + VII;
                    m(1, 0) = II + IV;
                    m(0, 1) = III + V;
                    m(1, 1) = I + III - II + VI;

                    return m;
                }

                size_t k = columns_ >> 1;

                SlicedMatrix<MT> A11(matrix, k, k);
                SlicedMatrix<MT> A12(matrix, 0, k, k, columns_);
                SlicedMatrix<MT> A21(matrix, k, columns_, 0, k);
                SlicedMatrix<MT> A22(matrix, k, columns_, k, columns_);

                SlicedMatrix<MT> B11(v.matrix, k, k);
                SlicedMatrix<MT> B12(v.matrix, 0, k, k, columns_);
                SlicedMatrix<MT> B21(v.matrix, k, columns_, 0, k);
                SlicedMatrix<MT> B22(v.matrix, k, columns_, k, columns_);

                Matrix<MT> a11 = A11.toMatrix();
                Matrix<MT> a12 = A12.toMatrix();
                Matrix<MT> a21 = A21.toMatrix();
                Matrix<MT> a22 = A22.toMatrix();

                Matrix<MT> b11 = B11.toMatrix();
                Matrix<MT> b12 = B12.toMatrix();
                Matrix<MT> b21 = B21.toMatrix();
                Matrix<MT> b22 = B22.toMatrix();

                Matrix<MT> I = (a11 + a22).strassen_multiplication(b11 + b22);
                Matrix<MT> II = (a21 + a22).strassen_multiplication(b11);
                Matrix<MT> III = a11.strassen_multiplication(b12 - b22);
                Matrix<MT> IV = a22.strassen_multiplication(b21 - b11);
                Matrix<MT> V = (a11 + a12).strassen_multiplication(b22);
                Matrix<MT> VI = (a21 - a11).strassen_multiplication(b11 + b12);
                Matrix<MT> VII = (a12 - a22).strassen_multiplication(b21 + b22);

                auto c1 = I + IV - V + VII;
                auto c2 = III + V;
                auto c3 = II + IV;
                auto c4 = I - II + III + VI;

                m.insert_matrix(c1, 0, 0);
                m.insert_matrix(c2, 0, k);
                m.insert_matrix(c3, k, 0);
                m.insert_matrix(c4, k, k);
                return m;
            }
            else
            {
                throw std::invalid_argument("Strassen Multiplication: needs square matrices atm");
            }
        }

        Matrix<T> toMatrix()
        {
            Matrix<T>
                m(rows_, columns_);

            const auto T_size = sizeof(T);
            const auto len = T_size * columns_;
            for (size_t i = 0; i < rows_; i++)
            {
                // r + row_start, c + column_start;
                memcpy(m.matrix_ + columns_ * i, matrix->pointer(row_start + i, column_start), len);
            }

            return m;
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