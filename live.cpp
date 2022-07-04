#include <fstream>
#include <sstream>

#include "menu.cpp"
int main() {
    matrix dist_m;
    std::ifstream dist_file("matrix/dist.txt");
    if (!dist_file.is_open()) {
        std::cout << "Error opening file\n";
        return 1;
    }
    std::string line;
    while (std::getline(dist_file, line)) {
        std::vector<number> row;
        std::stringstream ss(line);
        std::string item;
        while (std::getline(ss, item, ' ')) {
            if (item == "-1")
                row.push_back(INF);
            else if (!item.empty())
                row.push_back(atof(item.c_str()));
        }
        dist_m.push_back(row);
    }

    matrix time_m;
    std::ifstream time_file("matrix/time.txt");
    if (!time_file.is_open()) {
        std::cout << "Error opening file\n";
        return 1;
    }
    while (std::getline(time_file, line)) {
        std::vector<number> row;
        std::stringstream ss(line);
        std::string item;
        while (std::getline(ss, item, ' ')) {
            if (item == "-1")
                row.push_back(INF);
            else if (!item.empty())
                row.push_back(atof(item.c_str()));
        }
        time_m.push_back(row);
    }
    // read from matrix/cities.txt
    std::ifstream cities_file("matrix/cities.txt");
    if (!cities_file.is_open()) {
        std::cout << "Error opening file\n";
        return 1;
    }
    std::vector<std::string> cities;
    while (std::getline(cities_file, line)) {
        cities.push_back(line);
    }
    // read from matrix/names.txt
    std::ifstream names_file("matrix/names.txt");
    if (!names_file.is_open()) {
        std::cout << "Error opening file\n";
        return 1;
    }
    std::vector<std::string> names;
    while (std::getline(names_file, line)) {
        names.push_back(line);
    }

    // utils::print_matrix(dist_m);
    // utils::print_matrix(time_m);
    matrix suma_m;
    for (int i = 0; i < dist_m.size(); i++) {
        std::vector<number> row;
        for (int j = 0; j < dist_m[i].size(); j++) {
            row.push_back(dist_m[i][j] + time_m[i][j]);
        }
        suma_m.push_back(row);
    }
    std::vector<matrix> matrices{dist_m, time_m, suma_m};
    std::vector<std::string> ids{"dist", "time", "suma"};
    std::cout << "\n";
    for (int i = 0; i < matrices.size(); i++) {
#ifndef sec
        auto start = omp_get_wtime();
#else
        auto start = utils::cpu_time();
#endif
        TSP a;
        a.run(matrices[i]);

#ifndef sec
        auto finish = omp_get_wtime();
#else
        auto finish = utils::cpu_time();
#endif
        auto elapsed = finish - start;
        std::cout << "MATRIZ " << ids[i] << "\n";
        std::cout << "Elapsed time: " << elapsed << " s\n";
        auto best_path = a.get_path();
        for (int z = 0; z < best_path.size(); z++) {
            if (z == best_path.size() - 1)
                std::cout << cities[best_path[z]] << "\n";
            else
                std::cout << cities[best_path[z]] << " --> ";
        }
        for (int z = 0; z < best_path.size(); z++) {
            if (z == best_path.size() - 1)
                std::cout << names[best_path[z]] << "\n";
            else
                std::cout << names[best_path[z]] << " --> ";
        }
        std::cout << "\nMinimum ";
        if (ids[i] == "dist") {
            std::cout << "distance: ";
            std::cout << a.get_cost() / 1000 << " km\n";
        } else if (ids[i] == "time") {
            std::cout << "time: ";
            std::cout << a.get_cost() / 60 << " min\n";
        } else {
            std::cout << "cost: ";
            std::cout << a.get_cost() << " (m + s)\n";
        }
        std::cout << "\n";
    }
    return 0;
}
