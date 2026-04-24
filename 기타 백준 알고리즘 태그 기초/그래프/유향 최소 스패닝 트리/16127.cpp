// 16127(미생물 키우기) 문제 : https://www.acmicpc.net/problem/16127
// 알고리즘 태그 목록
/*
그래프 이론
유향 최소 스패닝 트리
*/
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

struct Edge {
    int from;
    int to;
    int weight;
    Edge(int u, int v, int w) : from(u), to(v), weight(w) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> required_qty(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> required_qty[i];
    }

    vector<vector<int>> weight_matrix(N + 1, vector<int>(N + 1, INF));
    vector<Edge> edges;

    for (int from = 0; from <= N; ++from) {
        for (int to = 1; to <= N; ++to) {
            cin >> weight_matrix[from][to];
            if (from != to) {
                edges.emplace_back(from, to, weight_matrix[from][to]);
            }
        }
    }

    int currentent_nodes = N;
    long long mst_cost = 0;

    while (true) {
        vector<int> min_in_weight(currentent_nodes + 1, INF);
        vector<int> min_in_from(currentent_nodes + 1, -1);
        
        min_in_weight[0] = 0;

        for (const auto& edge : edges) {
            if (min_in_weight[edge.to] > edge.weight) {
                min_in_weight[edge.to] = edge.weight;
                min_in_from[edge.to] = edge.from;
            }
        }

        for (int i = 1; i <= currentent_nodes; ++i) {
            mst_cost += min_in_weight[i];
        }

        vector<int> label(currentent_nodes + 1, -1);
        label[0] = 0;
        int next_node_count = 0;

        for (int i = 1; i <= currentent_nodes; ++i) {
            if (label[i] == -1) {
                int current = i;
                while (label[current] == -1) {
                    label[current] = -2;
                    current = min_in_from[current];
                }

                if (label[current] == -2) {
                    ++next_node_count;
                    while (label[current] == -2) {
                        label[current] = next_node_count;
                        current = min_in_from[current];
                    }
                }

                current = i;
                while (label[current] == -2) {
                    label[current] = ++next_node_count;
                    current = min_in_from[current];
                }
            }
        }

        if (next_node_count == currentent_nodes) {
            break;
        }

        vector<Edge> new_edges;
        for (const auto& edge : edges) {
            int u = label[edge.from];
            int v = label[edge.to];

            if (u != v) {
                new_edges.emplace_back(u, v, edge.weight - min_in_weight[edge.to]);
            }
        }
        edges.swap(new_edges);
        currentent_nodes = next_node_count;
    }

    for (int to = 1; to <= N; ++to) {
        int min_direct_cost = INF;
        for (int from = 0; from <= N; ++from) {
            min_direct_cost = min(min_direct_cost, weight_matrix[from][to]);
        }

        mst_cost += 1LL * (required_qty[to] - 1) * min_direct_cost;
    }

    cout << mst_cost << "\n";

    return 0;
}