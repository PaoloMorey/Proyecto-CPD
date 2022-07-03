#include <omp.h>

#include <algorithm>
#include <chrono>
#include <ctime>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

#define INF 10e6

using number = double;
using matrix = std::vector<std::vector<number>>;
using vector = std::vector<int>;
using pair = std::pair<std::vector<int>, std::pair<matrix, number>>;

struct my_comp {
    constexpr bool operator()(pair &p1, pair &p2) const noexcept {
        return p1.second.second > p2.second.second;
    }
};

using pq = std::priority_queue<pair, std::vector<pair>, my_comp>;

struct utils {
    static double cpu_time() {
        double value;
        value = (double)clock() / (double)CLOCKS_PER_SEC;
        return value;
    }

    static double calc_inf(double a, double b, char op = '-') {
        if (a == INF || b == INF) return INF;
        if (op == '-') return a - b;
        return a + b;
    }

    static void print_matrix(const matrix &matrix) {
        for (const auto &r : matrix) {
            for (auto c : r) {
                if (c != INF)
                    std::cout << c << "\t";
                else
                    std::cout << "inf"
                              << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "--------------------------\n";
    }

    static std::vector<int> func(std::vector<int> a, std::vector<int> b) {
        std::vector<int> ans;
        for (auto e : a) {
            if (std::find(b.begin(), b.end(), e) == b.end()) ans.push_back(e);
        }
        return ans;
    }

    static void print_vector(const vector &vector) {
        for (auto e : vector) std::cout << e << "\t";
        std::cout << "\n";
    }

    static void print_vertexes(const std::vector<int> &vector) {
        for (auto e : vector) std::cout << e << "\t";
        std::cout << "\n";
    }
};
