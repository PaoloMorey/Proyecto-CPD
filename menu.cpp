#include "tsp.cpp"

struct menu{
private:
    matrix adj;
    std::vector<std::string> cities{};

public:
    menu() = default;

    void run(){
        int N;
        number distance;
        std::string city;
        do{
            std::cout<<"Ingrese numero de ciudades: ";
            std::cin>>N; 
        } while (N < 2);
        matrix m(N);
        for (int i = 0; i < N; ++i){
            std::vector<number> v(N);
            m[i] = v;
        }
        adj = m;
        for(int i = 0; i < N; ++i){
            std::cout<<"\nIngrese ciudad "<<i+1<<": ";
            std::cin>>city;
            cities.push_back(city);
        }
        for (int i = 0; i < N; ++i){
            for(int j = i; j < N; ++j){
                if (i == j) adj[i][j] = INF;
                else{
                    std::cout<<"\nIngrese la distancia entre "<<cities[i]<<" a "<<cities[j]<<": ";
                    std::cin>>distance;
                    adj[i][j] = adj[j][i] = distance;
                }
            }
        } 
    }

    matrix get_adj(){
        return adj;
    }

    std::vector<std::string> get_cities(){
        return cities;
    }

};