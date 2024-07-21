#include "transformation.hpp"

namespace lin_alg
{
    Coordinate TransformationMatrix::operator*(const Coordinate &coord)
    {
        Coordinate coord_(0, 0, 0);
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; i < 3; i++)
            {
                coord_[i] += operator()(i, j) * coord[j];
            }
        }

        return coord_;
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
        transposed = false;
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
