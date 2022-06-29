#include "utils.cpp"

struct TSP {
private:
    vector path{};
    number cost{};

    static matrix fill_with_inf(matrix matrix, int prev, int curr, int start) {
        for (int i = 0; i < matrix.size(); ++i) {
            matrix[prev][i] = INF;
            matrix[i][curr] = INF;
        }
        matrix[curr][start] = INF;
        return matrix;
    }

    static std::pair<matrix, number>
    find_new_reduced_pair(const std::vector<std::pair<matrix, number>> &candidates, int &i) {
        std::pair<matrix, number> new_reduced_pair = candidates[0];
        for (int j = 0; j < candidates.size(); ++j) {
            if (candidates[j].second < new_reduced_pair.second) {
                new_reduced_pair = candidates[j];
                i = j;
            }
        }
        return new_reduced_pair;
    }

    static std::pair<matrix, number> reduced_matrix(const matrix &original) {
        number min, cost = 0;
        matrix reduced = original;
        for (auto &i: reduced) {
            min = *min_element(i.begin(), i.end());
            for (double &j: i) j = utils::calc_inf(j, min);
            if (min != INF) cost += min;
        }
        for (int j = 0; j < reduced[0].size(); ++j) {
            min = INF;
            for (auto &i: reduced) if (i[j] < min) min = i[j];
            for (auto &i: reduced) i[j] = utils::calc_inf(i[j], min);
            if (min != INF) cost += min;
        }
        return {reduced, cost};
    }

public:
    TSP() = default;

    void run(const matrix &adj, int start = 0) {
        std::vector<int> vertexes(adj.size());
        std::iota(std::begin(vertexes), std::end(vertexes), 0);
        path.push_back(start);
        vertexes.erase(std::find(vertexes.begin(), vertexes.end(), start));
        auto reduced = reduced_matrix(adj);
        while (path.size() != adj.size()) {
            std::vector<std::pair<matrix, number>> candidates;
            for (auto vertex: vertexes) {
                auto new_reduced = fill_with_inf(reduced.first, path.back(), vertex, start);
                auto new_reduced_pair = reduced_matrix(new_reduced);
                new_reduced_pair.second = reduced.first[path.back()][vertex] + reduced.second + new_reduced_pair.second;
                candidates.push_back(new_reduced_pair);
            }
            int i = 0;
            reduced = find_new_reduced_pair(candidates, i);
            path.push_back(vertexes[i]);
            vertexes.erase(vertexes.begin() + i);
        }
        path.push_back(start);
        this->cost = reduced.second;
    }

    vector get_path() {
        return path;
    }

    [[nodiscard]] number get_cost() const {
        return cost;
    }
};

