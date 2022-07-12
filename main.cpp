#include "cube.h"
#include "graphics.h"

int main()
{
    uint8_t v[6][9] = {
        {2, 4, 1, 0, 1, 1, 4, 4, 0},
        {4, 5, 3, 5, 3, 2, 4, 5, 1},
        {5, 0, 1, 3, 2, 2, 5, 3, 2},
        {0, 2, 5, 2, 3, 4, 4, 0, 3},
        {5, 4, 0, 1, 0, 1, 1, 5, 4},
        {0, 0, 2, 1, 2, 3, 3, 3, 5}};
    RubiksCube c(v);
    c.print_cube();
    c.shuffle();
    c.solve();
}
