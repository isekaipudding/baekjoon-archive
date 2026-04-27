// 11657(타임머신) 문제 : https://www.acmicpc.net/problem/11657
// 알고리즘 태그 목록
/*
그래프 이론
최단 경로
벨만–포드
*/
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

// 간선 정보를 저장하기 위한 구조체
struct Edge {
    int from, to, cost;
};

const ll INF = 1e18; // 충분히 큰 값 설정

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<Edge> edges;
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<ll> dist(N + 1, INF);
    dist[1] = 0;

    bool negative_cycle = false;

    // N번 반복 (N-1번은 최단 거리 확정, 마지막 1번은 음수 사이클 판별)
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < M; j++) {
            int u = edges[j].from;
            int v = edges[j].to;
            int cost = edges[j].cost;

            // 출발지가 방문 가능한 지역이고, 더 짧은 경로를 찾은 경우
            if (dist[u] != INF && dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;

                // N번째 반복에서도 갱신이 일어난다면 음수 사이클이 존재함
                if (i == N) {
                    negative_cycle = true;
                }
            }
        }
    }

    // 결과 출력
    if (negative_cycle) {
        cout << -1 << "\n";
    } else {
        for (int i = 2; i <= N; i++) {
            if (dist[i] == INF) cout << -1 << "\n";
            else cout << dist[i] << "\n";
        }
    }

    return 0;
}