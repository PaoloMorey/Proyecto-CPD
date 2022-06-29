#include <chrono>

#include "tsp.cpp"
int main() {
    std::vector<std::string> districts = {"Cercado", "Lince", "Miraflores", "Barranco", "Rimac", "Los Olivos",
                                          "La Molina", "La Victoria", "Magdalena", "San Borja"};
    matrix adj = {
        {INF, 5.3, 10, 11.8, 3.5, 12.5, 21.4, 6.5, 6.9, 10.3},
        {5.3, INF, 4.3, 7.7, 7.7, 17.5, 13.6, 2.8, 5.2, 6},
        {10, 4.3, INF, 2.9, 13.9, 23.7, 16.6, 8.3, 7.1, 9},
        {11.8, 7.7, 2.9, INF, 15, 24.8, 17.7, 9.4, 9.8, 10.1},
        {3.5, 7.7, 13.9, 15, INF, 14.3, 21.5, 9.3, 9.9, 13.1},
        {12.5, 17.5, 23.7, 24.8, 14.3, INF, 31.7, 18, 19, 27.9},
        {21.4, 13.6, 16.6, 17.7, 21.5, 31.7, INF, 14.6, 17.3, 9.3},
        {6.5, 2.8, 8.3, 9.4, 9.3, 18, 14.6, INF, 8.8, 4.7},
        {6.9, 5.2, 7.1, 9.8, 9.9, 19, 17.3, 8.8, INF, 9.5},
        {10.3, 6, 9, 10.1, 13.1, 27.9, 9.3, 4.7, 9.5, INF}};

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
        // for (int i : b) std::cout << districts[i] << "\t";
        // std::cout << "\nMinimum distance:  " << a.get_cost() << "\n";
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    for (int i : best_path) std::cout << districts[i] << "\t";
    std::cout << "\nMinimum distance:  " << best_cost << "\n";
    return 0;
}
