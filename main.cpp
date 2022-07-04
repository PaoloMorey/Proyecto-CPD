
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
    auto best_path = a.get_path();

    for (int z = 0; z < best_path.size(); z++) {
        if (z == best_path.size() - 1)
            std::cout << districts[best_path[z]] << "\n";
        else
            std::cout << districts[best_path[z]] << " --> ";
    }
    for (int z = 0; z < best_path.size(); z++) {
        if (z == best_path.size() - 1)
            std::cout << best_path[z] << "\n";
        else
            std::cout << best_path[z] << " --> ";
    }
    std::cout << "\nMinimum distance:  " << best_cost << "\n";
    return 0;
}
