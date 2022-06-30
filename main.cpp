#include "menu.cpp"

int main() {   
    menu A;
    A.run();
    auto adj = A.get_adj();
    auto districts = A.get_cities();
    auto start = std::chrono::high_resolution_clock::now();
    vector best_path;
    number best_cost = INF;
    for (int j = 0; j < adj.size(); ++j) {
        TSP a;
        a.run(adj, j);

        auto b = a.get_path();
        if (a.get_cost() < best_cost) {
            best_cost = a.get_cost();
            best_path = b;
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    for (int i : best_path) std::cout << districts[i] << "\t";
    std::cout << "\nMinimum distance:  " << best_cost << "\n";
    return 0;
}
