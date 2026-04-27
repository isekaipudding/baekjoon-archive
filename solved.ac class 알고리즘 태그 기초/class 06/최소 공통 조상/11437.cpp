// 11437(LCA) 문제 : https://www.acmicpc.net/problem/11437
// 알고리즘 태그 목록
/*
그래프 이론
트리
최소 공통 조상
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 50001;
const int MAX_K = 17; // 2^16 = 65536 > 50000

vector<int> adj[MAX_N];
int depth[MAX_N];
int parent[MAX_K][MAX_N];
bool visited[MAX_N];

// 1. DFS를 사용하여 각 노드의 깊이와 1단계 부모(2^0)를 찾음
void dfs(int curr, int d) {
    visited[curr] = true;
    depth[curr] = d;
    for (int next : adj[curr]) {
        if (visited[next]) continue;
        parent[0][next] = curr;
        dfs(next, d + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 루트인 1번 노드부터 트리 구성 시작
    dfs(1, 0);

    // 2. 희소 배열(Sparse Table) 구성 : parent[k][i] = i의 2^k번째 조상
    for (int k = 1; k < MAX_K; k++) {
        for (int i = 1; i <= N; i++) {
            int intermediate = parent[k - 1][i];
            parent[k][i] = parent[k - 1][intermediate];
        }
    }

    int M;
    cin >> M;
    while (M--) {
        int u, v;
        cin >> u >> v;

        // u가 항상 더 깊은 노드가 되도록 설정
        if (depth[u] < depth[v]) swap(u, v);

        // [Step 1] 깊이 맞추기 : u를 v의 깊이까지 끌어올림
        for (int k = MAX_K - 1; k >= 0; k--) {
            if (depth[u] - depth[v] >= (1 << k)) {
                u = parent[k][u];
            }
        }

        // 깊이를 맞췄는데 u와 v가 같다면 그게 바로 LCA
        if (u == v) {
            cout << u << "\n";
            continue;
        }

        // [Step 2] 같이 올라가기 : 조상이 달라지는 지점까지 점프
        for (int k = MAX_K - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }

        // 마지막에 한 칸 더 올라가면 그곳이 LCA
        cout << parent[0][u] << "\n";
    }

    return 0;
}