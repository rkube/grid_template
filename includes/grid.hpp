/*
 * Defines a 1-dimensional simulation domain where most quantities
 * are compile-time constants
 */

#pragma once
#include <iostream>

template<int N>
class Grid
{
    public:
        Grid() : y0(0.3), L(1.0), dx0(L / (N + 2)) {
            // Initialize the first grid point
            grid_points.at(0) = 0.0;

            // Initialize the grid perturbation
            dx.at(0) = 0.4;             // User-defined value at first element
            dx.at(N-2) = dx.at(0);      // The same user-defined value at last element
            dx.at((N-2) / 2) = -dx.at(N - 2) - dx.at(0);     // Middle element is sum of first and last

            dx.at((N - 2) / 4) = 0.0;       // Middle element of left interval
            dx.at((3 * N - 6)/ 4) = 0.0;    // Middle element of right interval

            // Initialize the lower and upper interval
            double delta{0.0};
            for (size_t i = 1; i < (N-2)/4; i++)
            {
                delta = y0 * ((4.0 * i - N + 2.0) / (6.0 - N));
                dx.at(i) = delta;
                // Use symmetry to fill the upper half of the left grid interval
                dx.at((N-2)/2 - i) = -delta;

                // Use symmetry to fill the lower hald of the upper grid interval
                dx.at((N-2) / 2 + i) = -delta;
                // Use symmetry to fill the upper half of the right grid interval
                dx.at(N - i - 2) = dx.at(i);
            }

            double sum_dx{0.0};
            for (auto it: dx)
                sum_dx += it;
            std::cout << "Total sum of grid perturbation is " << sum_dx << std::endl;

        }

        double get_length() const {
            return L;
        }

        double get_dx(size_t i) const {
            return dx.at(i);
        }

    private:
        std::array<double, N> grid_points; // The grid points
        std::array<double, N - 1> dx; // The grid spacing from left point to the right
        const double y0; // Initial delta for grid spacing 
        const double L;  // The length of the grid
        const double dx0;
};