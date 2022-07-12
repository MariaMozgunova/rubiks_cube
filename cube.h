#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>
#include <cctype>
#include <random>
#include <stdexcept>

using u32 = uint_least32_t;
using engine = std::mt19937;

class RubiksCube {
private:
    uint8_t cube[6][9];
public:
    RubiksCube(uint8_t in[6][9]);
    RubiksCube(std::ifstream& in);
    int seq_perm(std::vector<uint8_t>& seq);
    uint8_t color_to_prime(uint8_t color);
    int edge_to_color(uint8_t i);
    int corner_to_color(uint8_t i);
    int edge_perm();
    int corner_perm();
    int corner_or();
    void prepare_cube();
    int edge_or();
    void validate_cube();
    void rotate_facelet(int i);
    void print_facelet(int j, std::ostream& out = std::cout);
    void print_cube(std::ostream& out = std::cout);
    void F(bool visualization_required = 1);
    void R(bool visualization_required = 1);
    void B(bool visualization_required = 1);
    void L(bool visualization_required = 1);
    void U(bool visualization_required = 1);
    void D(bool visualization_required = 1);
    void Fprime();
    void Rprime();
    void Bprime();
    void Lprime();
    void Uprime();
    void Dprime();
    void assign_facelet(uint8_t* facelet, uint8_t* other);
    void x(bool visualization_required = 1);
    void y(bool visualization_required = 1);
    void z(bool visualization_required = 1);
    void xprime();
    void yprime();
    void zprime();
    void freeD(int j);
    void step1();
    void solve_LFU();
    void solve_RFU();
    void solve_BRU();
    void solve_BLU();
    void step2();
    void alg2();
    void alg3();
    void step3();
    void alg5();
    void step4();
    void alg6();
    void alg7();
    void step5();
    void alg8();
    void step6();
    void alg9();
    void alg10();
    void step7();
    void solve();
    void rotate(uint8_t cmd);
    void shuffle();
    bool need_to_rotate(uint8_t cmd, uint8_t i, uint8_t j);
    uint8_t name_color(uint8_t i, uint8_t j);
};
