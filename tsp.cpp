#include "utils.cpp"

struct TSP {
   private:
    vector path{};
    number cost{};

    static matrix fill_with_inf(matrix matrix, int prev, int curr, int start) {
        int i;
        for (i = 0; i < matrix.size(); ++i) {
            matrix[prev][i] = INF;
            matrix[i][curr] = INF;
        }
        matrix[curr][start] = INF;

        return matrix;
    }

    static std::pair<int, std::pair<matrix, number>>
    find_new_reduced_pair(const std::vector<std::pair<int, std::pair<matrix, number>>> &candidates) {
        std::pair<int, std::pair<matrix, number>> new_reduced_pair = candidates[0];
        for (int j = 0; j < candidates.size(); ++j) {
            if (candidates[j].second.second < new_reduced_pair.second.second) {
                new_reduced_pair = candidates[j];
            }
        }
        return {new_reduced_pair};
    }

    static std::pair<int, std::pair<matrix, number>> reduced_matrix(const matrix &original, int vertex) {
        number min, cost = 0;
        matrix reduced = original;
        for (auto &i : reduced) {
            min = *min_element(i.begin(), i.end());
            for (double &j : i) j = utils::calc_inf(j, min);
            if (min != INF) cost += min;
        }
        for (int j = 0; j < reduced[0].size(); ++j) {
            min = INF;
            for (auto &i : reduced)
                if (i[j] < min) min = i[j];
            for (auto &i : reduced) i[j] = utils::calc_inf(i[j], min);
            if (min != INF) cost += min;
        }
        return {vertex, {reduced, cost}};
    }

   public:
    TSP() = default;

    void run(const matrix &adj, int start = 0) {
        std::vector<int> vertexes(adj.size());
        std::iota(std::begin(vertexes), std::end(vertexes), 0);
        path.push_back(start);
        vertexes.erase(std::find(vertexes.begin(), vertexes.end(), start));
        auto reduced = reduced_matrix(adj, start);
        while (path.size() != adj.size()) {
            std::vector<std::pair<int, std::pair<matrix, number>>> candidates;
            int j = 0;
#pragma omp parallel for private(j) shared(reduced)
            for (j = 0; j < vertexes.size(); j++) {
                auto new_reduced = fill_with_inf(reduced.second.first, path.back(), vertexes[j], start);
                auto new_reduced_pair = reduced_matrix(new_reduced, vertexes[j]);
                new_reduced_pair.second.second = reduced.second.first[path.back()][vertexes[j]] + reduced.second.second + new_reduced_pair.second.second;
#pragma omp critical
                candidates.push_back(new_reduced_pair);
            }
            reduced = find_new_reduced_pair(candidates);
            path.push_back(reduced.first);
            vertexes.erase(std::find(vertexes.begin(), vertexes.end(), reduced.first));
        }
        path.push_back(start);
        this->cost = reduced.second.second;
    }

    vector get_path() {
        return path;
    }

    [[nodiscard]] number get_cost() const {
        return cost;
    }
};
