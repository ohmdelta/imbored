#ifndef TORUS_HPP
#define TORUS_HPP

#include <lin_alg.hpp>

#include "shapes.hpp"
#include "polynomial.hpp"

namespace renderer
{
    inline double sq(double v) { return v * v; }
    inline double cube(double v) { return v * v * v; }
    inline double supercube(double v) { return sq(v) * sq(v); }

    struct Torus : public Shape
    {
        Torus(
            double ring_radius_,
            double torus_radius_,
            lin_alg::Coordinate origin_ = lin_alg::Coordinate(0, 0, 0)) : ring_radius(ring_radius_),
                                                                          torus_radius(torus_radius_),
                                                                          origin(origin_) {}

        void set_origin(const lin_alg::Coordinate &origin_) override
        {
            origin = origin_;
        }

        lin_alg::Vector normal(const lin_alg::Coordinate &c)
        {
            // TODO: FIX THIS
            double norm = sqrt(sq(c.x) + sq(c.y));
            double x = c.x * torus_radius / norm;
            double y = c.y * torus_radius / norm;
            lin_alg::Coordinate torus_point(x, y, 0);
            // double theta = std::acos(c[1] / c[0]);
            // double phi = std::acos(c[2] / c[1]);

            // c[0] + c[1];
            return c - (origin - c) * -1;
        }

        void set_rotation(lin_alg::TransformationMatrix t)
        {
            rotation = t;
        }

        lin_alg::Coordinate line_intersection(
            lin_alg::Coordinate p0,
            lin_alg::Coordinate d)
        {
            p0 -= origin;
            d = rotation * d;
            p0 = rotation * p0;

            double R = torus_radius;
            double r = ring_radius;

            // double alpha = p0.norm_sq();
            // double beta = p0.dot(d);
            // double gamma = d.norm_sq();
            // double delta = gamma + sq(torus_radius) - sq(ring_radius);
            // double sigma = gamma - sq(torus_radius) - sq(ring_radius);

            // double a = alpha * alpha;
            // double b = 4 * alpha * beta;
            // double c = 2 * alpha * (gamma + sq(torus_radius) - sq(ring_radius))
            // - 4 * sq(torus_radius) * (sq(d[0]) + sq(d[1])) + 4 * sq(beta);

            double a = p0[0];
            double b = p0[1];
            double c = p0[2];

            double s_x = d[0];
            double s_y = d[1];
            double s_z = d[2];

            double R2 = sq(R);
            double r2 = sq(r);

            double R4 = supercube(R);
            double r4 = supercube(r);

            double a2 = sq(a);
            double b2 = sq(b);
            double c2 = sq(c);

            double a4 = supercube(a);
            double b4 = supercube(b);
            double c4 = supercube(c);

            double s_x2 = sq(s_x);
            double s_y2 = sq(s_y);
            double s_z2 = sq(s_z);

            double e_ = R4 - 2 * R2 * a2 - 2 * R2 * b2 + 2 * R2 * c2 - 2 * R2 * r2 + a4 + 2 * a2 * b2 + 2 * a2 * c2 - 2 * a2 * r2 + b4 + 2 * b2 * c2 - 2 * b2 * r2 + c4 - 2 * c2 * r2 + r4;

            double a_ = (pow(s_x, 4) + 2 * s_x2 * s_y2 + 2 * s_x2 * s_z2 + pow(s_y, 4) + 2 * s_y2 * s_z2 + pow(s_z, 4));
            double b_ = (4 * a * pow(s_x, 3) + 4 * a * s_x * s_y2 + 4 * a * s_x * s_z2 + 4 * b * s_x2 * s_y + 4 * b * pow(s_y, 3) + 4 * b * s_y * s_z2 + 4 * c * s_x2 * s_z + 4 * c * s_y2 * s_z + 4 * c * pow(s_z, 3));
            double c_ = (-2 * R2 * s_x2 - 2 * R2 * s_y2 + 2 * R2 * s_z2 + 6 * a2 * s_x2 + 2 * a2 * s_y2 + 2 * a2 * s_z2 + 8 * a * b * s_x * s_y + 8 * a * c * s_x * s_z + 2 * b2 * s_x2 + 6 * b2 * s_y2 + 2 * b2 * s_z2 + 8 * b * c * s_y * s_z + 2 * c2 * s_x2 + 2 * c2 * s_y2 + 6 * c2 * s_z2 - 2 * r2 * s_x2 - 2 * r2 * s_y2 - 2 * r2 * s_z2);
            double d_ = (-4 * R2 * a * s_x - 4 * R2 * b * s_y + 4 * R2 * c * s_z + 4 * pow(a, 3) * s_x + 4 * a2 * b * s_y + 4 * a2 * c * s_z + 4 * a * b2 * s_x + 4 * a * c2 * s_x - 4 * a * r2 * s_x + 4 * pow(b, 3) * s_y + 4 * b2 * c * s_z + 4 * b * c2 * s_y - 4 * b * r2 * s_y + 4 * pow(c, 3) * s_z - 4 * c * r2 * s_z);

            auto intersections_mu = polynomial::solve_quartic(a_, b_, c_, d_, e_);

            lin_alg::Coordinate result(0, 0, 0);

            if (intersections_mu.num_solutions == 0)
            {
                result.a = 0;
                return result;
            }
            else
            {
                auto min_mu = intersections_mu.min();
                result += p0 + d * min_mu;
                return result;
            }
        }

    private:
        double ring_radius;
        double torus_radius;

        lin_alg::Coordinate origin;

        lin_alg::TransformationMatrix rotation = lin_alg::Identity();
    };
};

#endif