// 1281(보석상) 문제 : https://www.acmicpc.net/problem/1281
// 알고리즘 태그 목록
/*
그래프 이론
최대 유량
최소 비용 최대 유량
헝가리안
선형 계획법
쌍대성
*/
#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    int capacity;
    int cost;
    int rev;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> jewels(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> jewels[i][j];
        }
    }

    int S = N + M;
    int T = N + M + 1;
    vector<vector<Edge>> graph(N + M + 2);

    auto add_edge = [&](int u, int v, int cap, int cost) {
        graph[u].push_back({v, cap, cost, (int)graph[v].size()});
        graph[v].push_back({u, 0, -cost, (int)graph[u].size() - 1});
    };

    for (int i = 0; i < N; i++) {
        add_edge(S, i, 1, 0);
    }

    for (int i = 0; i < M; i++) {
        add_edge(N + i, T, 1, 0);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            add_edge(i, N + j, 1, -jewels[i][j]);
        }
    }

    long long total_flow = 0;
    long long total_cost = 0;

    while (true) {
        vector<long long> distance(N + M + 2, INF);
        vector<int> parent_node(N + M + 2, -1);
        vector<int> parent_edge(N + M + 2, -1);
        vector<bool> in_queue(N + M + 2, false);
        queue<int> q;

        distance[S] = 0;
        q.push(S);
        in_queue[S] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            in_queue[current] = false;

            for (int i = 0; i < (int)graph[current].size(); i++) {
                Edge &edge = graph[current][i];
                if (edge.capacity > 0 && distance[edge.to] > distance[current] + edge.cost) {
                    distance[edge.to] = distance[current] + edge.cost;
                    parent_node[edge.to] = current;
                    parent_edge[edge.to] = i;
                    if (!in_queue[edge.to]) {
                        q.push(edge.to);
                        in_queue[edge.to] = true;
                    }
                }
            }
        }

        if (distance[T] == INF) break;

        int flow = 1e9;
        for (int i = T; i != S; i = parent_node[i]) {
            int prev = parent_node[i];
            int index = parent_edge[i];
            flow = min(flow, graph[prev][index].capacity);
        }

        for (int i = T; i != S; i = parent_node[i]) {
            int prev = parent_node[i];
            int index = parent_edge[i];
            graph[prev][index].capacity -= flow;
            int rev_index = graph[prev][index].rev;
            graph[i][rev_index].capacity += flow;
        }

        total_flow += flow;
        total_cost += (long long)flow * distance[T];
    }

    cout << -total_cost << "\n";

    return 0;
}