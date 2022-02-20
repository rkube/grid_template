/*
 * Defines a 1-dimensional simulation domain where most quantities
 * are compile-time constants
 */


template<int N>
class Grid
{
    public:
        Grid(double L_, double y0_) : L{L_}, y0{y0_} {
            // Unpertubed grid spacing
            constexpr double dx_0{L/N};
            // Initialize the first grid point
            grid_points[0] = 0.0;

            dx[0] = dx_0;

            // Initialize the grid spacing in the first half.
            double delta{0.0};
            for (size_t i = 1; i < (N-2)/4 - 1; i++)
            {
                delta = y0 * ((4.0 / (6.0 - N)) * i - (N-2.0)/(6.0-N));
                dx[i] = dx_0 + delta;
                // Use symmetry to fill the upper half of the left grid interval
                dx[(N-2)/2 - i] = dx_0 - delta;
            }
        }

        constexpr double get_length() const {
            return L;
        }

        constexpr double get_dx(int i) const {
            return dx[i];
        }

    private:
        std::array<double, N> grid_points; // The grid points
        std::array<double, N> dx; // The grid spacing from left point to the right
        const double L;  // The length of the grid
        const double y0; // Initial delta for grid spacing 
};