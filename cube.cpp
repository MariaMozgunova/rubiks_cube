#include "cube.h"
#include "graphics.h"

// http://kociemba.org/cube.htm
// https://en.wikipedia.org/wiki/Rubik%27s_Cube

// Sidenotes
// On the other hand it is well known that any even permutation can be achieved, as long as it doesn't try to interchange edges with corners.
// Corner parity: The sum of all orientations of corners must be divisible by three
// Edge parity: The sum of all orientations of edges must be even
// Thus, we only need to check corner and edge parity

// http://math.fon.rs/files/DanielsProject58.pdf <- Group Theory and the Rubik’s Cube
// https://cstheory.stackexchange.com/questions/47982/generating-a-pseudo-random-rubiks-cube-in-on2-epsilon-time
// https://medium.com/@benjamin.botto/implementing-an-optimal-rubiks-cube-solver-using-korf-s-algorithm-bf750b332cf9
// https://www.youtube.com/watch?v=ua7L34HAmuo
// https://math.stackexchange.com/questions/127577/how-to-tell-if-a-rubiks-cube-is-solvable
// https://www.quora.com/How-do-you-model-a-Rubiks-Cube-in-code
// http://www.math.rwth-aachen.de/~Martin.Schoenert/Cube-Lovers/David_Vanderschel__Orbit_Classification.html

std::random_device os_seed;
const u32 seed = os_seed();

engine generator(seed);
std::uniform_int_distribution<u32> command(0, 17);
std::uniform_int_distribution<u32> times(5, 100);

RubiksCube::RubiksCube(uint8_t in[6][9]) {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 9; ++j) {
            cube[i][j] = in[i][j];
        }
    }
}

RubiksCube::RubiksCube(std::ifstream& in) {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 9; ++j) {
            int k = 0;
            in >> k;
            cube[i][j] = k;
        }
    }
}

int RubiksCube::seq_perm(std::vector<uint8_t>& seq) {
    int res = 0;

    for (int i = 0; i < seq.size(); ++i) {
        for (int j = i + 1; j < seq.size(); ++j) {
            if (seq[i] > seq[j]) {
                ++res;
            }
        }
    }

    return res % 2;
}

uint8_t RubiksCube::color_to_prime(uint8_t color) {
    std::map<uint8_t, uint8_t> cp;
    cp[0] = 2;
    cp[1] = 3;
    cp[2] = 5;
    cp[3] = 11;
    cp[4] = 13;
    cp[5] = 17;

    return cp[color];
}

int RubiksCube::edge_to_color(uint8_t i) {
    switch (i) {
    case 0:
        return color_to_prime(cube[3][1]) * color_to_prime(cube[4][7]);
    case 1:
        return color_to_prime(cube[4][5]) * color_to_prime(cube[0][1]);
    case 2:
        return color_to_prime(cube[4][3]) * color_to_prime(cube[1][1]);
    case 3:
        return color_to_prime(cube[4][1]) * color_to_prime(cube[2][1]);
    case 4:
        return color_to_prime(cube[3][5]) * color_to_prime(cube[5][7]);
    case 5:
        return color_to_prime(cube[5][1]) * color_to_prime(cube[0][5]);
    case 6:
        return color_to_prime(cube[5][3]) * color_to_prime(cube[1][5]);
    case 7:
        return color_to_prime(cube[5][5]) * color_to_prime(cube[2][5]);
    case 8:
        return color_to_prime(cube[0][7]) * color_to_prime(cube[3][3]);
    case 9:
        return color_to_prime(cube[0][3]) * color_to_prime(cube[1][7]);
    case 10:
        return color_to_prime(cube[1][3]) * color_to_prime(cube[2][7]);
    }

    return color_to_prime(cube[3][7]) * color_to_prime(cube[2][3]);
}

int RubiksCube::corner_to_color(uint8_t i) {
    switch (i) {
    case 0:
        return color_to_prime(cube[4][6]) * color_to_prime(cube[0][0]) * color_to_prime(cube[3][2]);
    case 1:
        return color_to_prime(cube[4][4]) * color_to_prime(cube[0][2]) * color_to_prime(cube[1][0]);
    case 2:
        return color_to_prime(cube[1][2]) * color_to_prime(cube[4][2]) * color_to_prime(cube[2][0]);
    case 3:
        return color_to_prime(cube[4][0]) * color_to_prime(cube[2][2]) * color_to_prime(cube[3][0]);
    case 4:
        return color_to_prime(cube[3][4]) * color_to_prime(cube[5][0]) * color_to_prime(cube[0][6]);
    case 5:
        return color_to_prime(cube[5][2]) * color_to_prime(cube[0][4]) * color_to_prime(cube[1][6]);
    case 6:
        return color_to_prime(cube[5][4]) * color_to_prime(cube[1][4]) * color_to_prime(cube[2][6]);
    }

    return color_to_prime(cube[5][6]) * color_to_prime(cube[2][4]) * color_to_prime(cube[3][6]);
}

int RubiksCube::edge_perm() {
    std::map<uint8_t, uint8_t> home_pos;
    home_pos[143] = 0;
    home_pos[26] = 1;
    home_pos[39] = 2;
    home_pos[65] = 3;
    home_pos[187] = 4;
    home_pos[34] = 5;
    home_pos[51] = 6;
    home_pos[85] = 7;
    home_pos[22] = 8;
    home_pos[6] = 9;
    home_pos[15] = 10;
    home_pos[55] = 11;

    std::vector<uint8_t> seq(12);

    for (uint8_t i = 0; i < 12; ++i) {
        seq[i] = home_pos[edge_to_color(i)];
    }

    return seq_perm(seq);
}

int RubiksCube::corner_perm() {
    std::map<int, uint8_t> home_pos;
    home_pos[286] = 0;
    home_pos[78] = 1;
    home_pos[195] = 2;
    home_pos[715] = 3;
    home_pos[374] = 4;
    home_pos[102] = 5;
    home_pos[255] = 6;
    home_pos[935] = 7;

    std::vector<uint8_t> seq(8);

    for (uint8_t i = 0; i < 8; ++i) {
        seq[i] = home_pos[corner_to_color(i)];
    }

    return seq_perm(seq);
}

int RubiksCube::corner_or() {
    int res = 0;

    for (int i = 0; i < 4; ++i) {
        if (cube[0][0] == 4 || cube[0][0] == 5) {
            ++res;
        }
        else if (cube[3][2] == 4 || cube[3][2] == 5) {
            res += 2;
        }

        if (cube[3][4] == 4 || cube[3][4] == 5) {
            ++res;
        }
        else if (cube[0][6] == 4 || cube[0][6] == 5) {
            res += 2;
        }

        y();
    }

    return res % 3;
}

void RubiksCube::prepare_cube() {
    if (cube[4][8] != 4 && cube[5][8] != 4) {
        while (cube[0][8] != 4) {
            y();
        }

        x();
    }
    else if (cube[5][8] == 4) {
        z(); z();
    }

    while (cube[0][8] != 0) {
        y();
    }
}

int RubiksCube::edge_or() {
    int res = 0;

    for (int i = 0; i < 4; ++i) {
        if (cube[0][1] == cube[0][8]) {
            if (cube[4][5] == cube[1][8] || cube[4][5] == cube[3][8]) {
                ++res;
            }
        }
        else if (cube[4][5] == cube[0][8]) {
            if (cube[0][1] == cube[4][8] || cube[0][1] == cube[5][8]) {
                ++res;
            }
        }
        else if (cube[0][1] == cube[2][8]) {
            if (cube[4][5] == cube[1][8] || cube[4][5] == cube[3][8]) {
                ++res;
            }
        }
        else if (cube[4][5] == cube[2][8]) {
            if (cube[0][1] == cube[4][8] || cube[0][1] == cube[5][8]) {
                ++res;
            }
        }
        else if (cube[4][5] == cube[4][8] || cube[4][5] == cube[5][8]) {
            ++res;
        }


        if (cube[0][3] == cube[0][8]) {
            if (cube[1][7] == cube[4][8] || cube[1][7] == cube[5][8]) {
                ++res;
            }
        }
        else if (cube[1][7] == cube[0][8]) {
            if (cube[0][3] == cube[1][8] || cube[0][3] == cube[3][8]) {
                ++res;
            }
        }
        else if (cube[0][3] == cube[2][8]) {
            if (cube[1][7] == cube[4][8] || cube[1][7] == cube[5][8]) {
                ++res;
            }
        }
        else if (cube[1][7] == cube[2][8]) {
            if (cube[0][3] == cube[1][8] || cube[0][3] == cube[3][8]) {
                ++res;
            }
        }
        else if (cube[1][7] == cube[1][8] || cube[1][7] == cube[3][8]) {
            ++res;
        }


        if (cube[0][5] == cube[0][8]) {
            if (cube[5][1] == cube[1][8] || cube[5][1] == cube[3][8]) {
                ++res;
            }
        }
        else if (cube[5][1] == cube[0][8]) {
            if (cube[0][5] == cube[4][8] || cube[0][5] == cube[5][8]) {
                ++res;
            }
        }
        else if (cube[0][5] == cube[2][8]) {
            if (cube[5][1] == cube[1][8] || cube[5][1] == cube[3][8]) {
                ++res;
            }
        }
        else if (cube[5][1] == cube[2][8]) {
            if (cube[0][5] == cube[4][8] || cube[0][5] == cube[5][8]) {
                ++res;
            }
        }
        else if (cube[5][1] == cube[4][8] || cube[5][1] == cube[5][8]) {
            ++res;
        }


        y();
    }

    return res % 2;
}

void RubiksCube::validate_cube() {
    prepare_cube();

    std::cout << '\n';

    if (edge_perm() == corner_perm() && edge_or() == 0 && corner_or() == 0) {
        std::cout << "\nI can solve this cube :)\n";
        return;
    }

    throw std::logic_error("this cube can not be solved!");
}

void RubiksCube::rotate_facelet(int i) {
    for (int k = 0; k < 2; ++k) {
        uint8_t tmp = cube[i][7];

        for (int j = 7; j > 0; --j) {
            cube[i][j] = cube[i][j - 1];
        }

        cube[i][0] = tmp;
    }
}

void RubiksCube::print_facelet(int j, std::ostream& out) {
    std::map<uint8_t, char> color;
    color[0] = 'B';
    color[1] = 'O';
    color[2] = 'G';
    color[3] = 'R';
    color[4] = 'W';
    color[5] = 'Y';

    for (int i = 0; i < 9; ++i) {
        out << color[cube[j][i]];
    }

    out << '\n';
}

void RubiksCube::print_cube(std::ostream& out) {
    for (int i = 0; i < 6; ++i) {
        print_facelet(i, out);
    }

    out << '\n';
}

void RubiksCube::F() {
    solution.push_back(8);

    std::cout << "F";
    rotate_facelet(0);
    uint8_t tmp1 = cube[1][6];
    uint8_t tmp2 = cube[1][7];
    uint8_t tmp3 = cube[1][0];

    cube[1][6] = cube[4][4];
    cube[1][7] = cube[4][5];
    cube[1][0] = cube[4][6];

    cube[4][4] = cube[3][2];
    cube[4][5] = cube[3][3];
    cube[4][6] = cube[3][4];

    cube[3][2] = cube[5][0];
    cube[3][3] = cube[5][1];
    cube[3][4] = cube[5][2];

    cube[5][0] = tmp1;
    cube[5][1] = tmp2;
    cube[5][2] = tmp3;
}

void RubiksCube::R() {
    solution.push_back(4);

    std::cout << "R";
    rotate_facelet(1);
    uint8_t tmp1 = cube[2][6];
    uint8_t tmp2 = cube[2][7];
    uint8_t tmp3 = cube[2][0];

    cube[2][6] = cube[4][2];
    cube[2][7] = cube[4][3];
    cube[2][0] = cube[4][4];

    cube[4][2] = cube[0][2];
    cube[4][3] = cube[0][3];
    cube[4][4] = cube[0][4];

    cube[0][2] = cube[5][2];
    cube[0][3] = cube[5][3];
    cube[0][4] = cube[5][4];

    cube[5][2] = tmp1;
    cube[5][3] = tmp2;
    cube[5][4] = tmp3;
}

void RubiksCube::B() {
    solution.push_back(10);

    std::cout << "B";
    rotate_facelet(2);
    uint8_t tmp1 = cube[3][6];
    uint8_t tmp2 = cube[3][7];
    uint8_t tmp3 = cube[3][0];

    cube[3][6] = cube[4][0];
    cube[3][7] = cube[4][1];
    cube[3][0] = cube[4][2];

    cube[4][0] = cube[1][2];
    cube[4][1] = cube[1][3];
    cube[4][2] = cube[1][4];

    cube[1][2] = cube[5][4];
    cube[1][3] = cube[5][5];
    cube[1][4] = cube[5][6];

    cube[5][4] = tmp1;
    cube[5][5] = tmp2;
    cube[5][6] = tmp3;
}

void RubiksCube::L() {
    solution.push_back(6);

    std::cout << "L";
    rotate_facelet(3);
    uint8_t tmp1 = cube[0][6];
    uint8_t tmp2 = cube[0][7];
    uint8_t tmp3 = cube[0][0];

    cube[0][6] = cube[4][6];
    cube[0][7] = cube[4][7];
    cube[0][0] = cube[4][0];

    cube[4][6] = cube[2][2];
    cube[4][7] = cube[2][3];
    cube[4][0] = cube[2][4];

    cube[2][2] = cube[5][6];
    cube[2][3] = cube[5][7];
    cube[2][4] = cube[5][0];

    cube[5][6] = tmp1;
    cube[5][7] = tmp2;
    cube[5][0] = tmp3;
}

void RubiksCube::U() {
    solution.push_back(0);

    std::cout << "U";
    rotate_facelet(4);
    uint8_t tmp1 = cube[1][0];
    uint8_t tmp2 = cube[1][1];
    uint8_t tmp3 = cube[1][2];

    cube[1][0] = cube[2][0];
    cube[1][1] = cube[2][1];
    cube[1][2] = cube[2][2];

    cube[2][0] = cube[3][0];
    cube[2][1] = cube[3][1];
    cube[2][2] = cube[3][2];

    cube[3][0] = cube[0][0];
    cube[3][1] = cube[0][1];
    cube[3][2] = cube[0][2];

    cube[0][0] = tmp1;
    cube[0][1] = tmp2;
    cube[0][2] = tmp3;
}

void RubiksCube::D() {
    solution.push_back(2);

    std::cout << "D";
    rotate_facelet(5);
    uint8_t tmp1 = cube[1][4];
    uint8_t tmp2 = cube[1][5];
    uint8_t tmp3 = cube[1][6];

    cube[1][4] = cube[0][4];
    cube[1][5] = cube[0][5];
    cube[1][6] = cube[0][6];

    cube[0][4] = cube[3][4];
    cube[0][5] = cube[3][5];
    cube[0][6] = cube[3][6];

    cube[3][4] = cube[2][4];
    cube[3][5] = cube[2][5];
    cube[3][6] = cube[2][6];

    cube[2][4] = tmp1;
    cube[2][5] = tmp2;
    cube[2][6] = tmp3;
}

void RubiksCube::Fprime() {
    for (int i = 0; i < 3; ++i) {
        F();
    }
}

void RubiksCube::Rprime() {
    for (int i = 0; i < 3; ++i) {
        R();
    }
}

void RubiksCube::Bprime() {
    for (int i = 0; i < 3; ++i) {
        B();
    }
}

void RubiksCube::Lprime() {
    for (int i = 0; i < 3; ++i) {
        L();
    }
}

void RubiksCube::Uprime() {
    for (int i = 0; i < 3; ++i) {
        U();
    }
}

void RubiksCube::Dprime() {
    for (int i = 0; i < 3; ++i) {
        D();
    }
}

void RubiksCube::assign_facelet(uint8_t* facelet, uint8_t* other) {
    for (int i = 0; i < 9; ++i) {
        facelet[i] = other[i];
    }
}

void RubiksCube::x() {
    solution.push_back(12);

    std::cout << "x";

    uint8_t tmp[9];

    assign_facelet(tmp, cube[0]);
    assign_facelet(cube[0], cube[5]);
    assign_facelet(cube[5], cube[2]);
    assign_facelet(cube[2], cube[4]);
    assign_facelet(cube[4], tmp);

    rotate_facelet(2);
    rotate_facelet(2);
    rotate_facelet(5);
    rotate_facelet(5);
    rotate_facelet(1);
    rotate_facelet(3);
    rotate_facelet(3);
    rotate_facelet(3);
}

void RubiksCube::y() {
    solution.push_back(14);

    std::cout << "y";

    uint8_t tmp[9];

    assign_facelet(tmp, cube[0]);
    assign_facelet(cube[0], cube[1]);
    assign_facelet(cube[1], cube[2]);
    assign_facelet(cube[2], cube[3]);
    assign_facelet(cube[3], tmp);

    rotate_facelet(4);
    rotate_facelet(5);
    rotate_facelet(5);
    rotate_facelet(5);
}

void RubiksCube::z() {
    solution.push_back(16);

    std::cout << "z";

    uint8_t tmp[9];

    assign_facelet(tmp, cube[4]);
    assign_facelet(cube[4], cube[3]);
    assign_facelet(cube[3], cube[5]);
    assign_facelet(cube[5], cube[1]);
    assign_facelet(cube[1], tmp);

    rotate_facelet(1);
    rotate_facelet(5);
    rotate_facelet(3);
    rotate_facelet(4);
    rotate_facelet(0);
    rotate_facelet(2);
    rotate_facelet(2);
    rotate_facelet(2);
}

void RubiksCube::xprime() {
    for (int i = 0; i < 3; ++i) {
        x();
    }
}

void RubiksCube::yprime() {
    for (int i = 0; i < 3; ++i) {
        y();
    }
}

void RubiksCube::zprime() {
    for (int i = 0; i < 3; ++i) {
        z();
    }
}

void RubiksCube::freeD(int j) {
    while (cube[5][j] == 4) {
        D();
    }
}

void RubiksCube::step1() {
    while (cube[5][1] != 4 || cube[5][3] != 4 || cube[5][5] != 4 || cube[5][7] != 4) {
        while (cube[0][3] == 4) {
            freeD(3);

            Rprime();
        }

        while (cube[0][7] == 4) {
            freeD(7);

            L();
        }

        while (cube[1][3] == 4) {
            freeD(5);

            Bprime();
        }

        while (cube[1][7] == 4) {
            freeD(1);

            F();
        }

        while (cube[2][3] == 4) {
            freeD(7);

            Lprime();
        }

        while (cube[2][7] == 4) {
            freeD(3);

            R();
        }

        while (cube[3][3] == 4) {
            freeD(1);

            Fprime();
        }

        while (cube[3][7] == 4) {
            freeD(5);

            B();
        }

        std::cout << "1\n";
        print_cube();
        // check U for W
        if (cube[4][1] == 4) {
            freeD(5);
            B(); B();
        }

        if (cube[4][3] == 4) {
            freeD(3);
            R(); R();
        }

        if (cube[4][5] == 4) {
            freeD(1);
            F(); F();
        }

        if (cube[4][7] == 4) {
            freeD(7);
            L(); L();
        }

        std::cout << "2\n";
        print_cube();

        // side U and D edges
        if (cube[0][1] == 4) {
            freeD(1);
            F(); D(); Rprime();
        }

        if (cube[0][5] == 4) {
            freeD(1);
            Fprime(); D(); Rprime();
        }

        if (cube[1][1] == 4) {
            freeD(3);
            R(); D(); Bprime();
        }

        if (cube[1][5] == 4) {
            freeD(3);
            Rprime(); D(); Bprime();
        }

        if (cube[2][1] == 4) {
            freeD(5);
            B(); D(); Lprime();
        }

        if (cube[2][5] == 4) {
            freeD(5);
            Bprime(); D(); Lprime();
        }

        if (cube[3][1] == 4) {
            freeD(7);
            L(); D(); Fprime();
        }

        if (cube[3][5] == 4) {
            freeD(7);
            Lprime(); D(); Fprime();
        }
    }

    std::cout << "3\n";
    print_cube();

    // pull everything up towards white side
    while (cube[0][5] != 0) {
        D();
    }

    F(); F();

    while (!(cube[1][5] == 1 && cube[5][3] == 4)) {
        D();
    }

    R(); R();

    while (!(cube[2][5] == 2 && cube[5][5] == 4)) {
        D();
    }

    B(); B();

    while (!(cube[3][5] == 3 && cube[5][7] == 4)) {
        D();
    }

    L(); L();
}

void RubiksCube::solve_LFU() {
    if (cube[0][0] == 0 && cube[4][6] == 4 && cube[3][2] == 3) {
        return;
    }

    std::vector<uint8_t> LFU = { 0, 3, 4 };

    if (
        std::find(LFU.begin(), LFU.end(), cube[4][0]) != LFU.end() &&
        std::find(LFU.begin(), LFU.end(), cube[3][0]) != LFU.end() &&
        std::find(LFU.begin(), LFU.end(), cube[2][2]) != LFU.end()
        ) {
        Lprime(); D(); L();
    }

    if (
        std::find(LFU.begin(), LFU.end(), cube[4][2]) != LFU.end() &&
        std::find(LFU.begin(), LFU.end(), cube[1][2]) != LFU.end() &&
        std::find(LFU.begin(), LFU.end(), cube[2][0]) != LFU.end()
        ) {
        R(); D(); Rprime();
    }

    if (
        std::find(LFU.begin(), LFU.end(), cube[4][4]) != LFU.end() &&
        std::find(LFU.begin(), LFU.end(), cube[1][0]) != LFU.end() &&
        std::find(LFU.begin(), LFU.end(), cube[0][2]) != LFU.end()
        ) {
        Rprime(); Dprime(); R();
    }

    if (
        std::find(LFU.begin(), LFU.end(), cube[4][6]) != LFU.end() &&
        std::find(LFU.begin(), LFU.end(), cube[3][2]) != LFU.end() &&
        std::find(LFU.begin(), LFU.end(), cube[0][0]) != LFU.end()
        ) {
        Fprime(); D(); F();
    }

    while (!(
        std::find(LFU.begin(), LFU.end(), cube[5][0]) != LFU.end() &&
        std::find(LFU.begin(), LFU.end(), cube[3][4]) != LFU.end() &&
        std::find(LFU.begin(), LFU.end(), cube[0][6]) != LFU.end()
        )) {
        D();
    }

    while (
        !(cube[0][0] == 0 && cube[4][6] == 4 && cube[3][2] == 3)
        ) {
        Fprime(); Dprime(); F(); D();
    }
}

void RubiksCube::solve_RFU() {
    if (cube[0][2] == 0 && cube[4][4] == 4 && cube[1][0] == 1) {
        return;
    }

    std::vector<uint8_t> RFU = { 0, 1, 4 };

    if (
        std::find(RFU.begin(), RFU.end(), cube[4][2]) != RFU.end() &&
        std::find(RFU.begin(), RFU.end(), cube[1][2]) != RFU.end() &&
        std::find(RFU.begin(), RFU.end(), cube[2][0]) != RFU.end()
        ) {
        R(); D(); Rprime();
    }

    if (
        std::find(RFU.begin(), RFU.end(), cube[4][4]) != RFU.end() &&
        std::find(RFU.begin(), RFU.end(), cube[1][0]) != RFU.end() &&
        std::find(RFU.begin(), RFU.end(), cube[0][2]) != RFU.end()
        ) {
        Rprime(); D(); R();
    }

    if (
        std::find(RFU.begin(), RFU.end(), cube[4][0]) != RFU.end() &&
        std::find(RFU.begin(), RFU.end(), cube[3][0]) != RFU.end() &&
        std::find(RFU.begin(), RFU.end(), cube[2][2]) != RFU.end()
        ) {
        Lprime(); D(); L();
    }

    while (!(
        std::find(RFU.begin(), RFU.end(), cube[1][6]) != RFU.end() &&
        std::find(RFU.begin(), RFU.end(), cube[5][2]) != RFU.end() &&
        std::find(RFU.begin(), RFU.end(), cube[0][4]) != RFU.end()
        )) {
        D();
    }

    while (
        !(cube[0][2] == 0 && cube[4][4] == 4 && cube[1][0] == 1)
        ) {
        Rprime(); Dprime(); R(); D();
    }
}

void RubiksCube::solve_BRU() {
    if (cube[4][2] == 4 && cube[1][2] == 1 && cube[2][0] == 2) {
        return;
    }

    std::vector<uint8_t> BRU = { 1, 2, 4 };

    if (
        std::find(BRU.begin(), BRU.end(), cube[4][2]) != BRU.end() &&
        std::find(BRU.begin(), BRU.end(), cube[1][2]) != BRU.end() &&
        std::find(BRU.begin(), BRU.end(), cube[2][0]) != BRU.end()
        ) {
        R(); Dprime(); Rprime();
    }

    if (
        std::find(BRU.begin(), BRU.end(), cube[4][0]) != BRU.end() &&
        std::find(BRU.begin(), BRU.end(), cube[3][0]) != BRU.end() &&
        std::find(BRU.begin(), BRU.end(), cube[2][2]) != BRU.end()
        ) {
        Lprime(); D(); L();
    }

    while (!(
        std::find(BRU.begin(), BRU.end(), cube[1][4]) != BRU.end() &&
        std::find(BRU.begin(), BRU.end(), cube[5][4]) != BRU.end() &&
        std::find(BRU.begin(), BRU.end(), cube[2][6]) != BRU.end()
        )) {
        D();
    }

    while (
        !(cube[4][2] == 4 && cube[1][2] == 1 && cube[2][0] == 2)
        ) {
        Bprime(); Dprime(); B(); D();
    }
}

void RubiksCube::solve_BLU() {
    if (cube[4][0] == 4 && cube[2][2] == 2 && cube[3][0] == 3) {
        return;
    }

    std::vector<uint8_t> BLU = { 2, 3, 4 };

    if (
        std::find(BLU.begin(), BLU.end(), cube[4][0]) != BLU.end() &&
        std::find(BLU.begin(), BLU.end(), cube[3][0]) != BLU.end() &&
        std::find(BLU.begin(), BLU.end(), cube[2][2]) != BLU.end()
        ) {
        Lprime(); D(); L();
    }

    while (!(
        std::find(BLU.begin(), BLU.end(), cube[5][6]) != BLU.end() &&
        std::find(BLU.begin(), BLU.end(), cube[2][4]) != BLU.end() &&
        std::find(BLU.begin(), BLU.end(), cube[3][6]) != BLU.end()
        )) {
        D();
    }

    while (
        !(cube[4][0] == 4 && cube[2][2] == 2 && cube[3][0] == 3)
        ) {
        Lprime(); Dprime(); L(); D();
    }
}

void RubiksCube::step2() {
    solve_LFU();
    std::cout << '\n';
    print_cube();

    solve_RFU();
    std::cout << '\n';
    print_cube();

    solve_BRU();
    std::cout << '\n';
    print_cube();

    solve_BLU();
    std::cout << '\n';
    print_cube();
}

void RubiksCube::alg2() {
    // change edge's orientation
    R(); U(); U(); Rprime(); U(); R(); U(); U(); Rprime(); U(); Fprime(); Uprime(); F();
}

void RubiksCube::alg3() {
    //  place edge in the middle layer
    U(); R(); Uprime(); Rprime(); Uprime(); Fprime(); U(); F();
}

void RubiksCube::step3() {
    z(); z();

    // take wronge edges out of the middle layer
    for (int i = 0; i < 4; ++i) {
        if (!((cube[0][3] == cube[0][8] || cube[0][3] == cube[1][8]) && \
            (cube[1][7] == cube[0][8] || cube[1][7] == cube[1][8]) || \
            cube[0][3] == 5 || cube[1][7] == 5))
        {
            while (!(cube[0][1] == 5 || cube[4][5] == 5)) {
                U();
            }

            alg3();
        }

        y();
    }

    for (int i = 0; i < 4; ++i) {
        if (cube[0][3] == 5 || cube[1][7] == 5) {
            while (!((cube[0][1] == cube[0][8] || cube[0][1] == cube[1][8]) && \
                (cube[4][5] == cube[0][8] || cube[4][5] == cube[1][8]))) {
                U();
            }

            alg3();
        }

        if (cube[0][3] == cube[1][8]) {
            alg2();
        }

        y();
    }
}

void RubiksCube::alg5() {
    F(); R(); U(); Rprime(); Uprime(); Fprime();
}

void RubiksCube::step4() {
    if (cube[4][1] == 5 && cube[4][3] == 5 && cube[4][5] == 5 && cube[4][7] == 5) {
        return;
    }
    else if (cube[4][7] == 5 && cube[4][3] == 5) {
        alg5();
    }
    else if (cube[4][1] == 5 && cube[4][5] == 5) {
        U(); alg5();
    }
    else if (cube[4][1] != 5 && cube[4][3] != 5 && cube[4][5] != 5 && cube[4][7] != 5) {
        alg5(); alg5(); U(); alg5();
    }
    else {
        while (cube[4][1] != 5 || cube[4][7] != 5) {
            U();
        }

        alg5(); alg5();
    }
}

void RubiksCube::alg6() {
    Rprime(); U(); U(); R(); U(); Rprime(); U(); R();
}

void RubiksCube::alg7() {
    Uprime(); R(); Uprime(); Uprime(); Rprime(); Uprime(); R(); Uprime(); Rprime();
}

void RubiksCube::step5() {
    if (cube[4][0] == 5 && cube[4][2] == 5 && cube[4][4] == 5 && cube[4][6] == 5) {
        return;
    }

    if (cube[4][0] != 5 && cube[4][2] != 5 && cube[4][4] != 5 && cube[4][6] != 5) {
        while (!(cube[0][0] == 5 && cube[0][2] == 5)) {
            U();
        }

        if (cube[1][2] == 5) {
            alg6(); Uprime(); alg7(); Uprime(); alg7();
        }
        else {
            alg6(); alg6();
        }
    }
    else if (((cube[4][0] == 5) + (cube[4][2] == 5) + (cube[4][4] == 5) + (cube[4][6] == 5)) == 1) {
        std::cout << "case 2\n";
        while (cube[4][4] != 5) {
            U();
        }

        if (cube[0][0] == 5) {
            alg7();
        }
        else {
            alg6();
        }
    }
    else if ((cube[4][6] == 5 && cube[4][2] == 5) || (cube[4][0] == 5 && cube[4][4] == 5)) {
        while (!(cube[4][6] == 5 && cube[1][0] == 5)) {
            U();
        }

        alg6(); alg7();
    }
    else {
        while (cube[0][2] != 5) {
            U();
        }

        if (cube[4][2] == 5) {
            alg7(); U(); U(); alg6();
        }
        else {
            alg7(); alg6();
        }
    }
}

void RubiksCube::alg8() {
    R(); Bprime(); R(); F(); F(); Rprime(); B(); R(); F(); F(); R(); R();
}

void RubiksCube::step6() {
    if (cube[0][0] == cube[0][2] && cube[2][0] == cube[2][2]) {
        while (cube[0][8] != cube[0][0]) {
            U();
        }

        return;
    }

    uint8_t c = 6;

    for (int i = 0; i < 4; ++i) {
        if (cube[i][0] == cube[i][2]) {
            c = cube[i][0];
        }
    }

    if (c == 6) {
        alg8();

        step6();
        return;
    }

    while (cube[1][8] != c) {
        y();
    }

    while (cube[0][0] != c) {
        U();
    }

    alg8();
}

void RubiksCube::alg9() {
    R(); Uprime(); R(); U(); R(); U(); R(); Uprime(); Rprime(); Uprime(); R(); R();
}

void RubiksCube::alg10() {
    R(); R(); U(); R(); U(); Rprime(); Uprime(); Rprime(); Uprime(); Rprime(); U(); Rprime();
}

void RubiksCube::step7() {
    if (cube[0][1] == cube[0][8] && cube[1][1] == cube[1][8]) {
        return;
    }

    if (cube[0][1] == cube[2][8] && cube[2][1] == cube[0][8]) {
        alg9(); U(); alg9(); Uprime();
    }
    else if (cube[0][1] == cube[1][8] && cube[1][1] == cube[0][8]) {
        alg9(); Uprime(); alg9(); U();
    }
    else if (cube[0][1] == cube[3][8] && cube[3][1] == cube[0][8]) {
        y(); alg9(); Uprime(); alg9(); U();
    }
    else {
        while (cube[2][8] != cube[2][1]) {
            y();
        }

        if (cube[1][1] == cube[3][8]) {
            alg9();
        }
        else {
            alg10();
        }
    }
}

void RubiksCube::optimize_solution() {
    std::vector<uint8_t> temp;

    while (!solution.empty()) {
        uint8_t move = solution.back();
        solution.pop_back();
        uint8_t prime = (move / 2) * 2  + (1 ^ (move % 2));

        if (!solution.empty() && solution.back() == prime) {
            solution.pop_back();
        }
        else if ((solution.size() > 1) &&
            solution.back() == solution[solution.size() - 2] &&
            solution.back() == move) {
            solution.pop_back();
            solution.pop_back();
            solution.push_back(prime);
        }
        else {
            temp.push_back(move);
        }
    }

    std::reverse(temp.begin(), temp.end());
    solution = temp;
}

void RubiksCube::visualize_solution(RubiksCube& cube) {
    for (uint8_t move : solution) {
        vis::visualize_rotation(move, cube);
    
        cube.rotate(move);
    }
}

void RubiksCube::solve() {
    std::cout << "prepare your cube:\n";
    validate_cube();
    std::cout << "\nthe Rubik's Cube you get:\n";
    print_cube();

    solution.clear();
    RubiksCube copy = *this;

    std::cout << "\nsolve the white cross on U:\n";
    step1();
    std::cout << "\nthe Rubik's Cube you get:\n";
    print_cube();

    std::cout << "\nsolve four corner pieces on U:\n";
    step2();
    std::cout << "\nthe Rubik's Cube you get:\n";
    print_cube();

    std::cout << "\nsolve four edge pieces in the middle layer:\n";
    step3();
    std::cout << "\nthe Rubik's Cube you get:\n";
    print_cube();

    std::cout << "\nsolve the yellow edges:\n";
    step4();
    std::cout << "\nthe Rubik's Cube you get:\n";
    print_cube();

    std::cout << "\nsolve the yellow corners:\n";
    step5();
    std::cout << "\nthe Rubik's Cube you get:\n";
    print_cube();

    std::cout << "\norient the yellow corners:\n";
    step6();
    std::cout << "\nthe Rubik's Cube you get:\n";
    print_cube();

    std::cout << "\norient the yellow edges:\n";
    step7();
    std::cout << "\nthe Rubik's Cube is solved!!!:\n";
    print_cube();

    optimize_solution();

    vis::init();
    std::cout << "\nthe optimized solution:\n";
    visualize_solution(copy);
    vis::destroy();
}

void RubiksCube::rotate(uint8_t cmd) {
    switch (cmd) {
    case 0:
        U();
        break;
    case 1:
        Uprime();
        break;
    case 2:
        D();
        break;
    case 3:
        Dprime();
        break;
    case 4:
        R();
        break;
    case 5:
        Rprime();
        break;
    case 6:
        L();
        break;
    case 7:
        Lprime();
        break;
    case 8:
        F();
        break;
    case 9:
        Fprime();
        break;
    case 10:
        B();
        break;
    case 11:
        Bprime();
        break;
    case 12:
        x();
        break;
    case 13:
        xprime();
        break;
    case 14:
        y();
        break;
    case 15:
        yprime();
        break;
    case 16:
        z();
        break;
    case 17:
        zprime();
        break;
    }
}

void RubiksCube::shuffle() {
    int n = times(generator);

    for (int i = 0; i < n; ++i) {
        rotate(command(generator));
    }
}

bool RubiksCube::need_to_rotate(uint8_t cmd, uint8_t i, uint8_t j) {
    if (cmd == 0 || cmd == 1) {
        if (i == 4) {
            return true;
        }
        else if (i != 5 && (j == 0 || j == 1 || j == 2)) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (cmd == 2 || cmd == 3) {
        if (i == 5) {
            return true;
        }
        else if (i != 4 && (j == 4 || j == 5 || j == 6)) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (cmd == 4 || cmd == 5) {
        if (i == 1) {
            return true;
        }
        else if ((i == 0 || i == 4 || i == 5) && (j == 2 || j == 3 || j == 4)) {
            return true;
        }
        else if (i == 2 && (j == 0 || j == 6 || j == 7)) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (cmd == 6 || cmd == 7) {
        if (i == 3) {
            return true;
        }
        else if ((i == 0 || i == 4 || i == 5) && (j == 0 || j == 6 || j == 7)) {
            return true;
        }
        else if (i == 2 && (j == 2 || j == 3 || j == 4)) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (cmd == 8 || cmd == 9) {
        if (i == 0) {
            return true;
        }
        else if (i == 1 && (j == 0 || j == 6 || j == 7)) {
            return true;
        }
        else if (i == 3 && (j == 2 || j == 3 || j == 4)) {
            return true;
        }
        else if (i == 4 && (j == 4 || j == 5 || j == 6)) {
            return true;
        }
        else if (i == 5 && (j == 0 || j == 1 || j == 2)) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (cmd == 10 || cmd == 11) {
        if (i == 2) {
            return true;
        }
        else if (i == 1 && (j == 2 || j == 3 || j == 4)) {
            return true;
        }
        else if (i == 3 && (j == 0 || j == 6 || j == 7)) {
            return true;
        }
        else if (i == 4 && (j == 0 || j == 1 || j == 2)) {
            return true;
        }
        else if (i == 5 && (j == 4 || j == 5 || j == 6)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return true;
    }
}

uint8_t RubiksCube::name_color(uint8_t i, uint8_t j) {
    return cube[i][j];
}
