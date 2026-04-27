// 14567(선수과목 (Prerequisite)) 문제 : https://www.acmicpc.net/problem/14567
// 알고리즘 태그 목록
/*
다이나믹 프로그래밍
그래프 이론
방향 비순환 그래프
위상 정렬
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX = 1001;
vector<int> adj[MAX];
int in_degree[MAX];
int result[MAX];
int n, m;

int main() {
    // 1. 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    // 2. 그래프 인접 리스트 및 진입 차수 설정
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++; // v로 들어오는 간선 추가
    }

    // 3. 위상 정렬을 위한 큐 생성
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        // 진입 차수가 0인 과목(선수과목 없는 과목)은 1학기에 수강 가능
        if (in_degree[i] == 0) {
            q.push(i);
            result[i] = 1;
        }
    }

    // 4. 위상 정렬 수행하며 DP 업데이트
    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int next : adj[curr]) {
            in_degree[next]--;

            // 다음 과목의 이수 학기 = max(현재까지 구한 학기, 현재 과목 학기 + 1)
            // 사실 위상 정렬 순서대로 처리하므로 result[next] = result[curr] + 1로도 충분합니다.
            if (in_degree[next] == 0) {
                result[next] = result[curr] + 1;
                q.push(next);
            }
        }
    }

    // 5. 결과 출력
    for (int i = 1; i <= n; ++i) {
        cout << result[i] << " ";
    }
    cout << "\n";

    return 0;
}