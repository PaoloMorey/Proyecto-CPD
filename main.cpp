#include "menu.cpp"

int main() {
    menu A;
    A.run();
    auto adj = A.get_adj();
    auto districts = A.get_cities();
    auto start = std::chrono::high_resolution_clock::now();
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
    // find minimum in best_pc
    for (auto &i : best_pc) {
        if (i.second < best_cost) {
            best_cost = i.second;
            best_path = i.first;
        }
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "\n"
              << "Elapsed time: " << elapsed.count() << " s\n";
    for (int i : best_path) std::cout << districts[i] << "\t";
    std::cout << "\nMinimum distance:  " << best_cost << "\n";
    return 0;
}
