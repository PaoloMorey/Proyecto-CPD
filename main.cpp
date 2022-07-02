
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
    number best_cost = INF;
    std::vector<std::pair<vector, number>> best_pc;
    int j = 0;
#pragma omp parallel for private(j) schedule(dynamic)
    for (j = 0; j < adj.size(); ++j) {
        TSP a;
        a.run(adj, j);
#pragma omp critical
        best_pc.push_back({a.get_path(), a.get_cost()});
    }
    for (auto &i : best_pc) {
        if (i.second < best_cost) {
            best_cost = i.second;
            best_path = i.first;
        }
    }

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
