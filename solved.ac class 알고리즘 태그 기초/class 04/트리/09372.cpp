// 9372(상근이의 여행) 문제 : https://www.acmicpc.net/problem/9372
// 알고리즘 태그 목록
/*
그래프 이론
트리
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 전역 변수로 선언하여 bfs 함수에서 접근 가능하게 설정
int N, M;
vector<int> adj[1001];
bool visited[1001];

// 1번 노드부터 시작하여 연결된 정점의 개수를 카운트하는 BFS 함수
int bfs() {
    queue<int> q;
    int count = 0;

    q.push(1);
    visited[1] = true;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        count++;

        for (int next : adj[curr]) {
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        cin >> N >> M;

        // 매 테스트 케이스마다 인접 리스트와 방문 배열 초기화
        for (int i = 1; i <= N; ++i) {
            adj[i].clear();
            visited[i] = false;
        }

        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            // 무방향 그래프(왕복 비행기)이므로 양방향 추가
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // BFS 실행 후 (방문한 정점 수 - 1) 출력
        cout << bfs() - 1 << "\n";
        // 신장 트리의 성질에 의해 결과는 항상 N - 1이 됨
        // cout << N - 1 << "\n"; // 이 소스 코드가 더 효율적입니다.
    }

    return 0;
}