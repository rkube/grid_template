#include <iostream>
#include <array>
#include <cassert>
#include "includes/grid.hpp"

/*
 * Playground to play with compile-time initialized grids for numerical simulations.
 *
 * The idea is to have an uniform grid, as often used in numerical simulations that use an
 * unstructured grid. But this time, the grid is initialized at compile time. This project
 * explores how to make use of compile-time optimization, such as constexpr, when doing this.
 */


int main(void){
    constexpr int N{18};
    constexpr double L{1.0};
    constexpr double y0{0.3};
    static_assert((N/2) % 2 == 1);      // Formulas implemented require that N/2 is odd, f.ex. N=10, 18
    Grid<N> my_grid(L, y0);
    std::cout << "The length of the grid is: " << my_grid.get_length() << std::endl;
    for(int i = 0; i < N; i++){
        std::cout << "The grid spacing at point " << i << " is: " << my_grid.get_dx(i) << std::endl;
    }
}
