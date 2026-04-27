// 2207(가위바위보) 문제 : https://www.acmicpc.net/problem/2207
// 알고리즘 태그 목록
/*
그래프 이론
강한 연결 요소
2-sat
*/
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// 최대 변수의 개수 M (10,000), 노드는 참/거짓 두 개씩 필요하므로 20,000
const int MAX = 20005;

vector<int> adj[MAX];
int dfn[MAX], low[MAX], scc[MAX];
bool in_stack[MAX];
stack<int> st;
int timer, scc_count;

// 변수 x의 부정(NOT) 인덱스를 반환하는 함수
// i (1~M) 은 참, i+M 은 거짓으로 매핑
int neg(int x, int M) {
    return x > M ? x - M : x + M;
}

// 타잔 알고리즘으로 SCC 추출
void tarjan(int curr, int M) {
    dfn[curr] = low[curr] = ++timer;
    st.push(curr);
    in_stack[curr] = true;

    for (int next : adj[curr]) {
        if (!dfn[next]) {
            tarjan(next, M);
            low[curr] = min(low[curr], low[next]);
        } else if (in_stack[next]) {
            low[curr] = min(low[curr], dfn[next]);
        }
    }

    if (low[curr] == dfn[curr]) {
        scc_count++;
        while (true) {
            int t = st.top();
            st.pop();
            in_stack[t] = false;
            scc[t] = scc_count;
            if (t == curr) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;

        // 양수는 x (참), 음수는 M + |x| (거짓) 으로 매핑
        int u = (x > 0) ? x : M + abs(x);
        int v = (y > 0) ? y : M + abs(y);

        // (u OR v) 조건을 임플리케이션으로 변환: (NOT u -> v), (NOT v -> u)
        adj[neg(u, M)].push_back(v);
        adj[neg(v, M)].push_back(u);
    }

    // 모든 노드에 대해 SCC 수행
    for (int i = 1; i <= 2 * M; i++) {
        if (!dfn[i]) tarjan(i, M);
    }

    // 결과 판별 : i와 NOT i가 같은 SCC에 있으면 불가능(OTL)
    bool possible = true;
    for (int i = 1; i <= M; i++) {
        if (scc[i] == scc[i + M]) {
            possible = false;
            break;
        }
    }

    if (possible) cout << "^_^" << "\n";
    else cout << "OTL" << "\n";

    return 0;
}