#include <stdexcept>

#include "transformation.hpp"

namespace lin_alg
{
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

    TransformationMatrix TransformationMatrix::operator+(
        const TransformationMatrix &matrix)
    {
        TransformationMatrix coord_ = TransformationMatrix();
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; i < 3; i++)
            {
                coord_(i, j) += operator()(i, j) * matrix(i, j);
            }
        }

        return coord_;
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
