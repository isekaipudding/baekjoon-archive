// 18352(특정 거리의 도시 찾기) 문제 : https://www.acmicpc.net/problem/18352
// 알고리즘 태그 목록
/*
그래프 이론
그래프 탐색
너비 우선 탐색
최단 경로
데이크스트라
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 최대 도시 수와 거리 정보를 위한 상수 및 전역 변수
const int INF = 1e9;
int N, M, K, X;
vector<int> graph[300001];
int dist[300001];

/**
 * 시작 도시 X로부터 다른 모든 도시까지의 최단 거리를 계산합니다.
 * 모든 간선의 가중치가 1이므로 일반 Queue를 이용한 BFS로도 데이크스트라와 동일한 효과를 냅니다.
 */
void dijkstra(int start) {
    // 거리 배열을 -1(미방문)로 초기화
    fill(dist, dist + N + 1, -1);
    
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int next : graph[curr]) {
            // 아직 방문하지 않은 도시라면
            if (dist[next] == -1) {
                dist[next] = dist[curr] + 1;
                q.push(next);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // N: 도시 개수, M: 도로 개수, K: 목표 거리, X: 시작 도시
    cin >> N >> M >> K >> X;

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        // 단방향 도로 설정
        graph[u].push_back(v);
    }

    // 최단 경로 탐색 실행
    dijkstra(X);

    // 거리가 K인 도시들을 찾아 출력
    vector<int> result;
    for (int i = 1; i <= N; ++i) {
        if (dist[i] == K) {
            result.push_back(i);
        }
    }

    // 출력 결과 처리
    if (result.empty()) {
        cout << -1 << "\n";
    } else {
        // 도시 번호 오름차순 출력
        sort(result.begin(), result.end());
        for (int city : result) {
            cout << city << "\n";
        }
    }

    return 0;
}