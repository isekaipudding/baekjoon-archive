// 6086(최대 유량) 문제 : https://www.acmicpc.net/problem/6086
// 알고리즘 태그 목록
/*
구현
그래프 이론
시뮬레이션
최대 유량
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX = 52;
const int INF = 1e9;

int capacity[MAX][MAX];
int flow[MAX][MAX];
vector<int> adj[MAX];

// 문자를 인덱스로 변환 (A-Z: 0-25, a-z: 26-51)
int charToInt(char c) {
    if (c <= 'Z') return c - 'A';
    return c - 'a' + 26;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        char u_char, v_char;
        int c;
        cin >> u_char >> v_char >> c;

        int u = charToInt(u_char);
        int v = charToInt(v_char);

        // 양방향 간선 및 중복 간선 처리
        capacity[u][v] += c;
        capacity[v][u] += c;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int total_flow = 0;
    int source = charToInt('A');
    int sink = charToInt('Z');

    // 에드몬드-카프 알고리즘
    while (true) {
        vector<int> parent(MAX, -1);
        queue<int> q;
        q.push(source);

        while (!q.empty() && parent[sink] == -1) {
            int curr = q.front();
            q.pop();

            for (int next : adj[curr]) {
                // 잔여 용량이 남아 있고 아직 방문하지 않은 노드라면
                if (capacity[curr][next] - flow[curr][next] > 0 && parent[next] == -1) {
                    parent[next] = curr;
                    q.push(next);
                }
            }
        }

        // 더 이상 증가 경로가 없으면 종료
        if (parent[sink] == -1) break;

        // 찾은 경로에서 보낼 수 있는 최소 유량(amount) 계산
        int amount = INF;
        for (int i = sink; i != source; i = parent[i]) {
            amount = min(amount, capacity[parent[i]][i] - flow[parent[i]][i]);
        }

        // 유량 업데이트 (정방향은 더하고 역방향은 뺌)
        for (int i = sink; i != source; i = parent[i]) {
            flow[parent[i]][i] += amount;
            flow[i][parent[i]] -= amount;
        }

        total_flow += amount;
    }

    cout << total_flow << "\n";

    return 0;
}