// 12823(Critical Projects) 문제 : https://www.acmicpc.net/problem/12823
// 알고리즘 태그 목록
/*
그래프 이론
방향 비순환 그래프
위상 정렬
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N + 2);
    vector<int> inDegree(N + 2, 0);
    vector<int> outDegree(N + 2, 0);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        inDegree[v]++;
        outDegree[u]++;
    }

    int S = 0;
    int T = N + 1;
    for (int i = 1; i <= N; i++) {
        if (inDegree[i] == 0) {
            graph[S].push_back(i);
            inDegree[i]++;
            outDegree[S]++;
        }
        if (outDegree[i] == 0) {
            graph[i].push_back(T);
            inDegree[T]++;
            outDegree[i]++;
        }
    }

    queue<int> q;
    q.push(S);
    
    vector<int> topOrder;
    topOrder.reserve(N + 2);
    vector<int> ES(N + 2, 0);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topOrder.push_back(u);

        for (int v : graph[u]) {
            ES[v] = max(ES[v], ES[u] + 1);
            if (--inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    vector<int> LS(N + 2, 1e9);
    LS[T] = ES[T];
    for (int i = (int)topOrder.size() - 1; i >= 0; i--) {
        int u = topOrder[i];
        for (int v : graph[u]) {
            LS[u] = min(LS[u], LS[v] - 1);
        }
    }

    int max_time = ES[T];
    vector<int> active_count(max_time + 2, 0);
    for (int i = 1; i <= N; i++) {
        active_count[ES[i]]++;
        active_count[LS[i] + 1]--;
    }

    for (int t = 1; t <= max_time; t++) {
        active_count[t] += active_count[t - 1];
    }

    vector<int> criticalProjects;
    for (int i = 1; i <= N; i++) {
        if (active_count[ES[i]] == 1) {
            criticalProjects.push_back(i);
        }
    }

    if (criticalProjects.empty()) {
        cout << 0 << "\n";
    } else {
        sort(criticalProjects.begin(), criticalProjects.end());
        cout << criticalProjects.size() << "\n";
        for (size_t i = 0; i < criticalProjects.size(); i++) {
            cout << criticalProjects[i] << (i + 1 == criticalProjects.size() ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}