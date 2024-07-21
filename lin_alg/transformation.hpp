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

        Coordinate operator*(const Coordinate &coord);

        TransformationMatrix operator+(const TransformationMatrix &matrix);

        void transpose();

        friend std::ostream &operator<<(
            std::ostream &Str, TransformationMatrix &mc);

    private:
        bool transposed = false;
        double matrix[4][4]{0};

    protected:
        double &index(int i, int j)
        {
            return !transposed ? matrix[i][j] : matrix[j][i];
        }

        const double &index(int i, int j) const
        {
            return !transposed ? matrix[i][j] : matrix[j][i];
        }
    };

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