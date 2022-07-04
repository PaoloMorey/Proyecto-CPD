
#include "menu.cpp"

int main() {
    menu A;
    A.run();
    auto adj = A.get_adj();
    auto districts = A.get_cities();
#ifndef sec
    auto start = omp_get_wtime();
#else
    auto start = utils::cpu_time();
#endif
    vector best_path;

    TSP a;
    a.run(adj);
    number best_cost = a.get_cost();

#ifndef sec
    auto finish = omp_get_wtime();
#else
    auto finish = utils::cpu_time();
#endif
    auto elapsed = finish - start;
    std::cout << "\n"
              << "Elapsed time: " << elapsed << " s\n";
    // for (int i : best_path) std::cout << districts[i] << "\t";
    std::cout << "\nMinimum distance:  " << best_cost << "\n";
    return 0;
}
