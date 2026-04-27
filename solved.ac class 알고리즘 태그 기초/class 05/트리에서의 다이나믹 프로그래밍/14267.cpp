// 14267(회사 문화 1) 문제 : https://www.acmicpc.net/problem/14267
// 알고리즘 태그 목록
/*
다이나믹 프로그래밍
그래프 이론
그래프 탐색
트리
깊이 우선 탐색
트리에서의 다이나믹 프로그래밍
*/
#include <iostream>
#include <vector>

using namespace std;

// 최대 사원 수 설정
const int MAX = 100001;
vector<int> adj[MAX];
int score[MAX];
int n, m;

// DFS를 이용한 칭찬 전파 (Tree DP)
void dfs(int curr) {
    for (int next : adj[curr]) {
        // 상사의 칭찬 점수를 부하 직원에게 누적
        score[next] += score[curr];
        dfs(next);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    // 트리 인접 리스트 생성
    for (int i = 1; i <= n; i++) {
        int parent;
        cin >> parent;
        if (parent != -1) {
            adj[parent].push_back(i);
        }
    }

    // 초기 칭찬 점수 입력 (중복 칭찬이 가능하므로 += 연산)
    for (int i = 0; i < m; i++) {
        int employee, amount;
        cin >> employee >> amount;
        score[employee] += amount;
    }

    // 사장(1번)부터 시작하여 칭찬 전파
    dfs(1);

    // 결과 출력
    for (int i = 1; i <= n; i++) {
        cout << score[i] << " ";
    }
    cout << "\n";

    return 0;
}