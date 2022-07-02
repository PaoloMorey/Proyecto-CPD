#include "tsp.cpp"

struct menu {
   private:
    matrix adj;
    std::vector<std::string> cities{};

   public:
    menu() = default;

    void run() {
        int N;
        number distance;
        std::string city;
        std::cout << "¿Usar distritos de Lima?[Y/n] ";
        std::cin >> city;
        if (city == "Y") {
            // adj = {
            //     {INF, 5.3, 10, 11.8, 3.5, 12.5, 21.4, 6.5, 6.9, 10.3},
            //     {5.3, INF, 4.3, 7.7, 7.7, 17.5, 13.6, 2.8, 5.2, 6},
            //     {10, 4.3, INF, 2.9, 13.9, 23.7, 16.6, 8.3, 7.1, 9},
            //     {11.8, 7.7, 2.9, INF, 15, 24.8, 17.7, 9.4, 9.8, 10.1},
            //     {3.5, 7.7, 13.9, 15, INF, 14.3, 21.5, 9.3, 9.9, 13.1},
            //     {12.5, 17.5, 23.7, 24.8, 14.3, INF, 31.7, 18, 19, 27.9},
            //     {21.4, 13.6, 16.6, 17.7, 21.5, 31.7, INF, 14.6, 17.3, 9.3},
            //     {6.5, 2.8, 8.3, 9.4, 9.3, 18, 14.6, INF, 8.8, 4.7},
            //     {6.9, 5.2, 7.1, 9.8, 9.9, 19, 17.3, 8.8, INF, 9.5},
            //     {10.3, 6, 9, 10.1, 13.1, 27.9, 9.3, 4.7, 9.5, INF}};
            // cities = {"Cercado", "Lince", "Miraflores", "Barranco", "Rimac", "Los Olivos",
            //           "La Molina", "La Victoria", "Magdalena", "San Borja"};
            int total = 100;
            for (int i = 0; i < total; i++) {
                adj.push_back(std::vector<number>(total, INF));
            }

            for (int i = 0; i < total; i++) {
                for (int j = 0; j < total; j++) {
                    if (i == j) {
                        adj[i][j] = INF;
                    } else {
                        adj[i][j] = adj[j][i] =
                            std::rand() % (int)(100 * 100);
                    }
                }
            }

            return;
        }

        do {
            std::cout << "Ingrese numero de ciudades: ";
            std::cin >> N;
        } while (N < 2);
        matrix m(N);
        for (int i = 0; i < N; ++i) {
            std::vector<number> v(N);
            m[i] = v;
        }
        adj = m;
        for (int i = 0; i < N; ++i) {
            std::cout << "\nIngrese ciudad " << i + 1 << ": ";
            std::cin >> city;
            cities.push_back(city);
        }
        std::cout << "¿Desea insertar distancia entre las ciudades?[Y/n]: ";
        std::cin >> city;
        if (city == "Y") {
            for (int i = 0; i < N; ++i) {
                for (int j = i; j < N; ++j) {
                    if (i == j)
                        adj[i][j] = INF;
                    else {
                        std::cout << "\nIngrese la distancia entre " << cities[i] << " a " << cities[j] << ": ";
                        std::cin >> distance;
                        adj[i][j] = adj[j][i] = distance;
                    }
                }
            }
            return;
        }
    }

    matrix get_adj() {
        return adj;
    }

    std::vector<std::string> get_cities() {
        return cities;
    }
};