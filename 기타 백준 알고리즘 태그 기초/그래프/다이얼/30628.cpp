// 30628(김밥천국과 도로지옥) 문제 : https://www.acmicpc.net/problem/30628
// 알고리즘 태그 목록
/*
그래프 이론
최단 경로
데이크스트라
다이얼
*/
#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    int weight;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    long long K;
    cin >> K;

    vector<vector<Edge>> graph(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<vector<long long>> distance(N + 1, vector<long long>(12, INF));

    const int W = 10; 
    queue<pair<int, int>> buckets[W + 1];

    distance[1][0] = 0;
    buckets[0].push({1, 0});

    long long current_distance = 0;
    int total_elements = 1;

    for (; total_elements > 0; current_distance++) {
        int index = current_distance % (W + 1);

        while (!buckets[index].empty()) {
            pair<int, int> curr = buckets[index].front();
            int u = curr.first;
            int mod12 = curr.second;
            buckets[index].pop();
            total_elements--;

            if (distance[u][mod12] < current_distance) continue;

            for (auto& edge : graph[u]) {
                long long nextDist = distance[u][mod12] + edge.weight;
                int nextMod12 = nextDist % 12;

                if (distance[edge.to][nextMod12] > nextDist) {
                    distance[edge.to][nextMod12] = nextDist;
                    buckets[nextDist % (W + 1)].push({edge.to, nextMod12});
                    total_elements++;
                }
            }
        }
    }

    if (distance[N][K % 12] <= K) {
        cout << "YES" << "\n";
    } else {
        cout << "NO" << "\n";
    }

    return 0;
}