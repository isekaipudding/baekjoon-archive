// 9539(Escape) 문제 : https://www.acmicpc.net/problem/9539
// 알고리즘 태그 목록
/*
자료 구조
그리디 알고리즘
트리
집합과 맵
분리 집합
우선순위 큐
작은 집합에서 큰 집합으로 합치는 테크닉
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

struct Segment {
    long long req, gain;
    bool operator>(const Segment& o) const {
        if (req != o.req) return req > o.req;
        return gain < o.gain; 
    }
};

using PQ = priority_queue<Segment, vector<Segment>, greater<Segment>>;

int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_cnt;
long long H[MAXN];
int parent_node[MAXN];
bool on_path[MAXN];
PQ pqs[MAXN];

inline void add_edge(int u, int v) {
    to[++edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

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

void solve() {
    int N = readInt();
    int T_node = readInt();

    edge_cnt = 0;
    for (int i = 1; i <= N; i++) {
        head[i] = 0;
        on_path[i] = false;
        parent_node[i] = 0;
        pqs[i] = PQ();
        H[i] = readInt();
    }

    for (int i = 0; i < N - 1; i++) {
        int u = readInt(), v = readInt();
        add_edge(u, v);
        add_edge(v, u);
    }

    queue<int> q;
    q.push(1);
    parent_node[1] = -1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == T_node) break;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (parent_node[v] == 0) {
                parent_node[v] = u;
                q.push(v);
            }
        }
    }

    vector<int> path;
    int curr = T_node;
    while (curr != -1) {
        path.push_back(curr);
        on_path[curr] = true;
        curr = parent_node[curr];
    }
    reverse(path.begin(), path.end());

    while (!q.empty()) q.pop();
    vector<int> post_order;
    post_order.reserve(N);

    for (int u : path) {
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (!on_path[v]) {
                parent_node[v] = u;
                q.push(v);
            }
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        post_order.push_back(u);
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v != parent_node[u] && !on_path[v]) {
                parent_node[v] = u;
                q.push(v);
            }
        }
    }
    
    reverse(post_order.begin(), post_order.end());

    for (int u : post_order) {
        long long R = max(0LL, -H[u]);
        long long G = H[u];

        while (!pqs[u].empty()) {
            Segment top = pqs[u].top();
            if (G <= 0 || top.req <= R + G) {
                pqs[u].pop();
                R = max(R, top.req - G);
                G += top.gain;
            } else {
                break;
            }
        }

        if (G > 0) pqs[u].push({R, G});

        int p = parent_node[u];
        if (pqs[u].size() > pqs[p].size()) {
            swap(pqs[u], pqs[p]);
        }
        while (!pqs[u].empty()) {
            pqs[p].push(pqs[u].top());
            pqs[u].pop();
        }
    }

    PQ global_pq;
    long long current_HP = H[1];
    bool escaped = true;

    for (int i = 0; i < (int)path.size(); i++) {
        int u = path[i];
        if (u == T_node) break;

        if (pqs[u].size() > global_pq.size()) {
            swap(global_pq, pqs[u]);
        }
        while (!pqs[u].empty()) {
            global_pq.push(pqs[u].top());
            pqs[u].pop();
        }

        while (!global_pq.empty() && global_pq.top().req <= current_HP) {
            current_HP += global_pq.top().gain;
            global_pq.pop();
        }

        if (i + 1 < (int)path.size()) {
            int nxt = path[i + 1];
            long long req = max(0LL, -H[nxt]);
            if (current_HP < req) {
                escaped = false;
                break;
            }
            current_HP += H[nxt];
        }
    }

    if (escaped) cout << "escaped\n";
    else cout << "trapped\n";
}

int main() {
    int t = readInt();
    while (t--) solve();
    return 0;
}