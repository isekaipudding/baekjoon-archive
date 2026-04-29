// 3311(Traffic) 문제 : https://www.acmicpc.net/problem/3311
// 알고리즘 태그 목록
/*
그래프 이론
그래프 탐색
너비 우선 탐색
깊이 우선 탐색
방향 비순환 그래프
위상 정렬
강한 연결 요소
평면 그래프
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;
const int MAXM = 900005;
const int INF = 0x3f3f3f3f;

static inline int readInt() {
    static char buf[1 << 20];
    static int ptr = 0;
    static int len = 0;

    auto getChar = [&]() -> char {
        if (ptr == len) {
            len = fread(buf, 1, 1 << 20, stdin);
            ptr = 0;
            if (len == 0) return EOF;
        }
        return buf[ptr++];
    };

    int x = 0;
    char c = getChar();
    while (c != '-' && (c < '0' || c > '9')) c = getChar();
    
    bool neg = false;
    if (c == '-') { neg = true; c = getChar(); }
    
    for (; c >= '0' && c <= '9'; c = getChar()) x = x * 10 + (c - '0');
    return neg ? -x : x;
}

int N, M, A, B;
int X[MAXN], Y[MAXN];

int head[MAXN], to[MAXM], nxt[MAXM], edgeCount;
void addEdge(int u, int v) {
    to[++edgeCount] = v;
    nxt[edgeCount] = head[u];
    head[u] = edgeCount;
}

int dfn[MAXN], low[MAXN], timer;
int compId[MAXN], compCount;
bool onStack[MAXN];
stack<int> st;

bool canReachWest[MAXN];

void checkReachability() {
    vector<int> leftNodes;
    for (int i = 1; i <= N; i++) if (X[i] == 0) leftNodes.push_back(i);
    
    queue<int> q;
    for (int s : leftNodes) {
        canReachWest[s] = true;
        q.push(s);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = nxt[i]) {
            if (!canReachWest[to[i]]) {
                canReachWest[to[i]] = true;
                q.push(to[i]);
            }
        }
    }
}

void tarjan(int startNode) {
    static stack<pair<int, int>> dfsStack;
    dfsStack.push({startNode, head[startNode]});
    
    while (!dfsStack.empty()) {
        int u = dfsStack.top().first;
        int& i = dfsStack.top().second;

        if (dfn[u] == 0) {
            dfn[u] = low[u] = ++timer;
            st.push(u);
            onStack[u] = true;
        }

        bool pushed = false;
        for (; i; i = nxt[i]) {
            int v = to[i];
            if (dfn[v] == 0) {
                i = nxt[i];
                dfsStack.push({v, head[v]});
                pushed = true;
                break;
            } else if (onStack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (pushed) continue;

        if (low[u] == dfn[u]) {
            compCount++;
            while (true) {
                int node = st.top(); st.pop();
                onStack[node] = false;
                compId[node] = compCount;
                if (node == u) break;
            }
        }
        
        dfsStack.pop();
        if (!dfsStack.empty()) {
            low[dfsStack.top().first] = min(low[dfsStack.top().first], low[u]);
        }
    }
}

int lowRange[MAXN], highRange[MAXN];
vector<int> dag[MAXN];
int inDegree[MAXN];

void solve() {
    vector<pair<int, int>> eastNodes;
    for (int i = 1; i <= N; i++) {
        if (X[i] == A && canReachWest[i]) eastNodes.push_back({Y[i], i});
    }
    sort(eastNodes.begin(), eastNodes.end());

    for (int i = 1; i <= compCount; i++) {
        lowRange[i] = INF;
        highRange[i] = -1;
    }

    for (int i = 0; i < (int)eastNodes.size(); i++) {
        int c = compId[eastNodes[i].second];
        lowRange[c] = min(lowRange[c], i);
        highRange[c] = max(highRange[c], i);
    }

    for (int u = 1; u <= N; u++) {
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (compId[u] != compId[v]) {
                dag[compId[u]].push_back(compId[v]);
                inDegree[compId[v]]++;
            }
        }
    }

    queue<int> q;
    vector<int> topo;
    for (int i = 1; i <= compCount; i++) if (inDegree[i] == 0) q.push(i);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : dag[u]) if (--inDegree[v] == 0) q.push(v);
    }

    for (int i = (int)topo.size() - 1; i >= 0; i--) {
        int u = topo[i];
        for (int v : dag[u]) {
            if (highRange[v] != -1) {
                lowRange[u] = min(lowRange[u], lowRange[v]);
                highRange[u] = max(highRange[u], highRange[v]);
            }
        }
    }

    vector<pair<int, int>> westNodes;
    for (int i = 1; i <= N; i++) if (X[i] == 0) westNodes.push_back({-Y[i], i});
    sort(westNodes.begin(), westNodes.end());

    for (auto& p : westNodes) {
        int c = compId[p.second];
        int result = (highRange[c] == -1) ? 0 : (highRange[c] - lowRange[c] + 1);
        printf("%d\n", result);
    }
}

int main() {
    N = readInt(); M = readInt(); A = readInt(); B = readInt();
    for (int i = 1; i <= N; i++) {
        X[i] = readInt(); Y[i] = readInt();
    }
    for (int i = 0; i < M; i++) {
        int u = readInt(), v = readInt(), k = readInt();
        addEdge(u, v);
        if (k == 2) addEdge(v, u);
    }

    checkReachability();
    for (int i = 1; i <= N; i++) if (dfn[i] == 0) tarjan(i);
    
    solve();

    return 0;
}