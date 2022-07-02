#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <chrono>
#include <omp.h>

#define INF 1000

using number = double;
using matrix = std::vector<std::vector<number>>;
using vector = std::vector<int>;

struct utils {

    static double calc_inf(double a, double b, char op = '-') {
        if (a == INF || b == INF) return INF;
        if (op == '-') return a - b;
        return a + b;
    }

    static void print_matrix(const matrix &matrix) {
        for (const auto &r: matrix) {
            for (auto c: r) {
                if (c != INF) std::cout << c << "\t";
                else std::cout << "inf" << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "--------------------------\n";
    }


    static void print_vector(const vector &vector) {
        for (auto e: vector) std::cout << e << "\t";
        std::cout << "\n";
    }
};

