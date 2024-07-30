#include <stdexcept>

#include "transformation.hpp"

namespace lin_alg
{

    TransformationMatrix operator+(TransformationMatrix a, const TransformationMatrix &b)
    {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                a(i, j) += b(i, j);
            }
        }

        return a;
    }

    TransformationMatrix &TransformationMatrix::operator*=(double p)
    {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                matrix[i][j] *= p;
            }
        }

        return *this;
    }

    TransformationMatrix operator+(TransformationMatrix a, TransformationMatrix b)
    {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                a(i, j) += b(i, j);
            }
        }

        return a;
    }

    TransformationMatrix operator*(TransformationMatrix a, TransformationMatrix b)
    {
        TransformationMatrix c;
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                for (size_t k = 0; k < 4; k++)
                {
                    c(i, j) += a(i, k) * b(k, j);
                }
            }
        }

        return c;
    }

    Vector
    operator*(const TransformationMatrix &t, const Vector &p)
    {
        Vector c(0, 0, 0, 0);

        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                c[i] += t(i, j) * p(j);
            }
        }

        return c;
    }

    TransformationMatrix &TransformationMatrix::operator+=(const TransformationMatrix &matrix)
    {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                index(i, j) += matrix.index(i, j);
            }
        }
        return *this;
    }

    TransformationMatrix &TransformationMatrix::operator-=(const TransformationMatrix &matrix)
    {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                index(i, j) -= matrix.index(i, j);
            }
        }
        return *this;
    }

    TransformationMatrix
    operator+(TransformationMatrix t, double p)
    {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                t.index(i, j) += p;
            }
        }

        return t;
    }

    TransformationMatrix
    operator-(TransformationMatrix t, double p)
    {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                t.index(i, j) -= p;
            }
        }

        return t;
    }

    TransformationMatrix
    operator*(TransformationMatrix t, double p)
    {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                t.index(i, j) *= p;
            }
        }
        return t;
    }

    TransformationMatrix
    operator/(TransformationMatrix t, double p)
    {
        if (p == 0)
        {
            throw std::runtime_error("Math error: Attempted to divide by Zero\n");
        }

        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                t.index(i, j) /= p;
            }
        }
        return t;
    }

    void TransformationMatrix::transpose()
    {
        transposed ^= 1;
    }

    std::ostream &operator<<(
        std::ostream &Str, TransformationMatrix &mc)
    {
        for (size_t i = 0; i < 4; i++)
        {
            Str << "[ ";
            for (size_t j = 0; j < 4; j++)
            {
                Str << mc(i, j) << " ";
            }

            Str << "]" << std::endl;
        }
        return Str;
    }

}
