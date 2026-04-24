// 13367(Weeping Fig) 문제 : https://www.acmicpc.net/problem/13367
// 알고리즘 태그 목록
/*
그래프 이론
스토어–바그너
*/
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

void solve() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N + 1, vector<int>(N + 1, 0));
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] += w;
        graph[v][u] += w;
    }

    if (N <= 1) {
        cout << 0 << "\n";
        return;
    }

    int global_min_cut = INF;
    vector<int> active_nodes(N);
    iota(active_nodes.begin(), active_nodes.end(), 1);

    while (active_nodes.size() > 1) {
        vector<int> w(N + 1, 0);
        vector<bool> in_a(N + 1, false);
        int s = -1, t = -1;

        for (int i = 0; i < (int)active_nodes.size(); i++) {
            int next_node = -1;

            for (int u : active_nodes) {
                if (!in_a[u] && (next_node == -1 || w[u] > w[next_node])) {
                    next_node = u;
                }
            }

            s = t;
            t = next_node;
            in_a[t] = true;

            for (int u : active_nodes) {
                if (!in_a[u]) {
                    w[u] += graph[t][u];
                }
            }
        }

        global_min_cut = min(global_min_cut, w[t]);

        for (int u : active_nodes) {
            if (u != s && u != t) {
                graph[s][u] += graph[t][u];
                graph[u][s] += graph[t][u];
            }
        }

        active_nodes.erase(find(active_nodes.begin(), active_nodes.end(), t));
    }

    cout << global_min_cut << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }

    return 0;
}