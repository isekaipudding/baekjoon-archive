// 1506(경찰서) 문제 : https://www.acmicpc.net/problem/1506
// 알고리즘 태그 목록
/*
그래프 이론
강한 연결 요소
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

const int MAX = 101;
int N;
int cost[MAX];
vector<int> adj[MAX];     // 정방향 그래프
vector<int> rev_adj[MAX]; // 역방향 그래프
bool visited[MAX];
stack<int> st;

// 1. 정방향 DFS : 종료되는 순서대로 스택에 삽입
void dfs1(int curr) {
    visited[curr] = true;
    for (int next : adj[curr]) {
        if (!visited[next]) dfs1(next);
    }
    st.push(curr);
}

// 2. 역방향 DFS : 같은 SCC에 속한 노드들을 방문하며 최소 비용 탐색
void dfs2(int curr, int& min_val) {
    visited[curr] = true;
    min_val = min(min_val, cost[curr]);
    for (int next : rev_adj[curr]) {
        if (!visited[next]) dfs2(next, min_val);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    // 각 도시의 경찰서 건설 비용 입력
    for (int i = 1; i <= N; i++) {
        cin >> cost[i];
    }

    // 인접 행렬 형태의 도로 정보를 인접 리스트로 변환
    for (int i = 1; i <= N; i++) {
        string row;
        cin >> row;
        for (int j = 1; j <= N; j++) {
            if (row[j - 1] == '1') {
                adj[i].push_back(j);
                rev_adj[j].push_back(i);
            }
        }
    }

    // [Step 1] 정방향 DFS 수행하여 스택 채우기
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) dfs1(i);
    }

    // 방문 배열 초기화
    fill(visited, visited + MAX, false);

    long long total_cost = 0;

    // [Step 2] 스택에서 하나씩 꺼내며 역방향 DFS 수행 (SCC 추출)
    while (!st.empty()) {
        int curr = st.top();
        st.pop();

        if (!visited[curr]) {
            int component_min = 2e9; // 해당 SCC 내의 최소 비용
            dfs2(curr, component_min);
            total_cost += component_min;
        }
    }

    // 결과 출력
    cout << total_cost << "\n";

    return 0;
}