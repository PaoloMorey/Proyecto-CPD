#include "utils.cpp"

struct TSP {
   private:
    vector path{};
    number cost{};
    matrix adj{};
    int start{};
    std::vector<int> copy_vertex{};
    std::vector<pq> give_me_a_name{};

    matrix fill_with_inf(matrix matrix, int prev, int curr) {
        int i;
        for (i = 0; i < matrix.size(); ++i) {
            matrix[prev][i] = INF;
            matrix[i][curr] = INF;
        }
        matrix[curr][start] = INF;

        return matrix;
    }

    pair find_new_reduced_pair(pq &candidates) {
        auto ans = candidates.top();
        candidates.pop();
        give_me_a_name.push_back(candidates);
        return ans;
    }

    void check_upper() {
        for (int i = give_me_a_name.size() - 1; i >= 0; --i) {
            if (!give_me_a_name[i].empty()) {
                if (give_me_a_name[i].top().second.second < cost) {
                    auto temp = give_me_a_name[i].top();
                    give_me_a_name[i].pop();
                    give_me_a_name.resize(i + 1);
                    fill_path(temp, utils::func(copy_vertex, temp.first));
                }
            }
        }
    }

    pq find_candidates(vector vertexes, pair reduced) {
        pq candidates;
        int j;
#pragma omp parallel for private(j) shared(reduced)
        for (j = 0; j < vertexes.size(); j++) {
            auto new_reduced = fill_with_inf(reduced.second.first, reduced.first.back(), vertexes[j]);
            auto new_reduced_pair = reduced_matrix(new_reduced, vertexes[j], reduced.first);
            new_reduced_pair.second.second = reduced.second.first[reduced.first.back()][vertexes[j]] + reduced.second.second + new_reduced_pair.second.second;
#pragma omp critical
            candidates.push(new_reduced_pair);
        }
        return candidates;
    }

    static pair reduced_matrix(const matrix &original, int vertex, std::vector<int> vertexes_path) {
        number min, cost = 0;
        matrix reduced = original;
        vertexes_path.push_back(vertex);
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
        return {vertexes_path, {reduced, cost}};
    }

    void fill_path(pair reduced, std::vector<int> vertexes) {
        auto i = reduced.first.size();
        while (i != adj.size()) {
            auto candidates = find_candidates(vertexes, reduced);
            reduced = find_new_reduced_pair(candidates);
            vertexes.erase(std::find(vertexes.begin(), vertexes.end(), reduced.first[reduced.first.size() - 1]));
            i++;
        }
        if (reduced.second.second < this->cost) {
            this->cost = reduced.second.second;
            this->path = reduced.first;
        }
        check_upper();
    }

   public:
    TSP() = default;

    void run(const matrix &adj, int start = 0) {
        this->adj = adj;
        this->start = start;
        this->cost = INF;
        std::vector<int> vertexes(adj.size());
        std::iota(std::begin(vertexes), std::end(vertexes), 0);
        copy_vertex = vertexes;
        vertexes.erase(std::find(vertexes.begin(), vertexes.end(), start));
        std::vector<int> vertexes_path;
        auto reduced = reduced_matrix(adj, start, vertexes_path);
        fill_path(reduced, vertexes);
        this->path.push_back(start);
    }

    vector get_path() {
        return path;
    }

    [[nodiscard]] number get_cost() const {
        return cost;
    }
};
