// 7777(병원) 문제 : https://www.acmicpc.net/problem/7777
// 알고리즘 태그 목록
/*
그래프 이론
트리
최대 유량
도미네이터 트리
*/
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

struct DominatorFinder {
    int n, k;
    vector<vector<pii>> adj;
    vector<int> capacities;
    vector<pii> parent_edge;
    vector<bool> initially_reachable;

    DominatorFinder(int n, int k) : n(n), k(k) {
        adj.resize(2 * n + 2);
        parent_edge.assign(2 * n + 2, {-1, -1});
        initially_reachable.assign(2 * n + 2, false);
    }

    inline int vin(int x) { return x << 1; }
    inline int vout(int x) { return x << 1 | 1; }

    void add_edge(int u, int v, int cap = 1) {
        int edge_index = capacities.size();
        adj[u].push_back({v, edge_index});
        adj[v].push_back({u, edge_index | 1});
        capacities.push_back(cap);
        capacities.push_back(0);
    }

    vector<bool> get_reachability(int source) {
        vector<bool> visit(2 * n + 2, false);
        queue<int> q;

        q.push(source);
        visit[source] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (auto& edge : adj[current]) {
                int next_node = edge.first;
                int edge_index = edge.second;

                if (!visit[next_node] && capacities[edge_index] > 0) {
                    visit[next_node] = true;
                    q.push(next_node);
                }
            }
        }
        return visit;
    }

    void solve() {
        for (int i = 1; i <= n; ++i) {
            add_edge(vin(i), vout(i));
        }

        for (int i = 1; i <= k; ++i) {
            int d; cin >> d;
            while (d--) {
                int neighbor; cin >> neighbor;
                add_edge(vout(neighbor), vin(i));
            }
        }

        for (int i = k + 1; i <= n; ++i) {
            add_edge(0, vin(i));
        }

        queue<int> q;
        q.push(0);
        initially_reachable[0] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (auto& edge : adj[current]) {
                int next_node = edge.first;
                int edge_index = edge.second;
                if (!initially_reachable[next_node] && capacities[edge_index] > 0) {
                    initially_reachable[next_node] = true;
                    parent_edge[next_node] = {current, edge_index};
                    q.push(next_node);
                }
            }
        }

        vector<int> unreachable_hospitals;
        for (int i = 1; i <= n; ++i) {
            if (parent_edge[vout(i)].first == -1) {
                unreachable_hospitals.push_back(i);
            }
        }

        vector<pii> dominator_pairs;
        for (int x = 1; x <= n; ++x) {
            if (parent_edge[vout(x)].first == -1) continue;

            for (int e = 0; e < (int)capacities.size(); ++e) {
                capacities[e] = (e % 2 == 0 ? 1 : 0);
            }

            int current = vout(x);
            while (current != 0) {
                auto p = parent_edge[current];
                capacities[p.second] = 0;
                capacities[p.second ^ 1] = 1;
                current = p.first;
            }

            vector<bool> currentent_visit = get_reachability(0);

            for (int y = x + 1; y <= n; ++y) {
                if (parent_edge[vout(y)].first != -1 && !currentent_visit[vout(y)]) {
                    dominator_pairs.push_back({x, y});
                }
            }
        }

        cout << unreachable_hospitals.size() << "\n";
        for (int h : unreachable_hospitals) cout << h << " ";
        cout << "\n";

        cout << dominator_pairs.size() << "\n";
        if (dominator_pairs.size() <= 10000) {
            for (auto& p : dominator_pairs) {
                cout << p.first << " " << p.second << "\n";
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    DominatorFinder df(n, k);
    df.solve();

    return 0;
}