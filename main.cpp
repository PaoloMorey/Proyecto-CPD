#include <bits/stdc++.h>
#include <omp.h>

#include <vector>

using namespace std;

#define INF 1000

using matrix = vector<vector<double>>;

const int N = 5;

matrix adj = {
    {INF, 20, 30, 10, 11},
    {15, INF, 16, 4, 2},
    {3, 5, INF, 2, 4},
    {19, 6, 18, INF, 3},
    {16, 4, 7, 16, INF}};

void printMatrix(matrix &m) {
    for (auto row : m) {
        for (auto col : row) {
            if (col == INF)
                cout << "INF"
                     << "\t";
            else
                cout << col << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

double calc_inf(double a, double b, char op = '-') {
    if (a == INF || b == INF)
        return INF;
    if (op == '-')
        return a - b;
    return a + b;
}
matrix fillInf(int a, int b, matrix m, int start) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == a || j == b)
                m[i][j] = INF;
        }
    }
    m[b][start] = INF;
    return m;
}

pair<matrix, double> matrixCost(matrix &m) {
    double cost = 0, min;
    matrix newM;
    for (auto row : m) {
        min = *min_element(row.begin(), row.end());
        vector<double> temp;
        for (auto col : row) {
            temp.push_back(calc_inf(col, min, '-'));
        }
        newM.push_back(temp);
        cost += min;
    }
    printMatrix(newM);
    for (int j = 0; j < m[0].size(); j++) {
        min = INF;
        for (int i = 0; i < m.size(); i++) {
            if (newM[i][j] < min) {
                min = newM[i][j];
            }
        }
        cost += min;
        for (int i = 0; i < newM.size(); i++) {
            newM[i][j] = calc_inf(newM[i][j], min, '-');
        }
    }
    return {newM, cost};
}

void TSP(matrix adj, int start = 0) {
    auto res = matrixCost(adj);
    auto newM = res.first;
    auto cost = res.second;

    int path[N + 1];
    path[0] = start;

    vector<pair<matrix, double>> adjacents;

    for (int i = 0; i < N; i++) {
        if (i == start || newM[start][i] == INF)
            continue;
        auto newAdj = fillInf(start, i, newM, start);
        auto temp = matrixCost(newAdj);
        adjacents.push_back({temp.first, cost + temp.second});
    }

    // TODO: find the node with the lowest cost and call TSP_Recursive on it
}

void TSP_Recursive(matrix m, int path[], int curr, int level, int currCost) {
    path[level - 1] = curr;
    // TODO: Logic for the last level, check for connection to initial node and check if new path is shorter than previous one

    vector<pair<matrix, double>> adjacents;

    for (int i = 0; i < N; i++) {
        if (i == curr || m[curr][i] == INF)
            continue;
        auto newAdj = fillInf(curr, i, m, path[0]);
        auto temp = matrixCost(newAdj);
        adjacents.push_back({temp.first, currCost + temp.second});
    }

    // TODO: find the node with the lowest cost and call TSP_Recursive on it
}

int main() {
    printMatrix(adj);
    auto res = matrixCost(adj);
    printMatrix(res.first);
    cout << res.second << endl;
    return 0;
}