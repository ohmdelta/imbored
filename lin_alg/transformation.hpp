#ifndef TRANSFORMATION_HPP
#define TRANSFORMATION_HPP

#include <vector>
#include <cassert>
#include <ostream>

#include "coordinate.hpp"

namespace lin_alg
{
    class TransformationMatrix
    {
    public:
        TransformationMatrix() {}

        double &operator()(int r, int c) { return index(r, c); }
        const double &operator()(int r, int c) const { return index(r, c); };

        // Coordinate operator*(const Coordinate &coord);

        friend TransformationMatrix operator+(TransformationMatrix t, double p);
        friend TransformationMatrix operator-(TransformationMatrix t, double p);
        friend TransformationMatrix operator*(TransformationMatrix t, double p);
        friend TransformationMatrix operator/(TransformationMatrix t, double p);

        friend Coordinate operator*(const TransformationMatrix &t, const Coordinate &p);

        TransformationMatrix &operator*=(double p);
        TransformationMatrix &operator+=(const TransformationMatrix &matrix);
        TransformationMatrix &operator-=(const TransformationMatrix &matrix);

        TransformationMatrix &operator*=(const TransformationMatrix &t);

        TransformationMatrix operator+(const TransformationMatrix &matrix);

        void transpose();

        friend std::ostream &operator<<(
            std::ostream &Str, TransformationMatrix &mc);

    private:
        bool transposed = false;
        double matrix[4][4]{0};

    public:
        double &index(int i, int j)
        {
            return !transposed ? matrix[i][j] : matrix[j][i];
        }

        const double &index(int i, int j) const
        {
            return !transposed ? matrix[i][j] : matrix[j][i];
        }
    };

    inline bool operator==(const TransformationMatrix &lhs, const TransformationMatrix &rhs)
    {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                if (lhs(i, j) != rhs(i, j))
                    return false;
            }
        }

        return true;
    }

    inline bool operator!=(const TransformationMatrix &lhs, const TransformationMatrix &rhs) { return !(lhs == rhs); }

    class Identity : public TransformationMatrix
    {
    public:
        Identity()
        {
            for (size_t i = 0; i < 4; i++)
            {
                index(i, i) = 1;
            }
        }
    };

};

#endif