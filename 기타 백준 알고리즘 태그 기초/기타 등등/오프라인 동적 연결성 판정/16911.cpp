// 16911(그래프와 쿼리) 문제 : https://www.acmicpc.net/problem/13966
// 알고리즘 태그 목록
/*
자료 구조
그래프 이론
분리 집합
분할 정복
오프라인 쿼리
오프라인 동적 연결성 판정
*/
#include <bits/stdc++.h>

using namespace std;

struct Query {
    int type;
    int u, v;
};

const int MAX_M = 100005;
int N, M;
Query queries[MAX_M];
vector<pair<int, int>> tree[MAX_M * 4];

int parent_node[100005];
int sz[100005];
struct History {
    int u, v;
};
stack<History> history_stack;

void init_dsu(int n) {
    for (int i = 1; i <= n; ++i) {
        parent_node[i] = i;
        sz[i] = 1;
    }
}

int find_parent(int u) {
    while (u != parent_node[u]) {
        u = parent_node[u];
    }
    return u;
}

bool merge_nodes(int u, int v) {
    u = find_parent(u);
    v = find_parent(v);
    if (u == v) return false;
    
    if (sz[u] < sz[v]) swap(u, v);
    
    parent_node[v] = u;
    sz[u] += sz[v];
    history_stack.push({u, v});
    return true;
}

void rollback(int count) {
    while (count--) {
        int u = history_stack.top().u;
        int v = history_stack.top().v;
        history_stack.pop();
        
        sz[u] -= sz[v];
        parent_node[v] = v;
    }
}

void add_edge_to_tree(int node, int start, int end, int left, int right, pair<int, int> edge) {
    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        tree[node].push_back(edge);
        return;
    }
    int mid = (start + end) / 2;
    add_edge_to_tree(node * 2, start, mid, left, right, edge);
    add_edge_to_tree(node * 2 + 1, mid + 1, end, left, right, edge);
}

void solve(int node, int start, int end) {
    int merge_count = 0;
    for (auto& edge : tree[node]) {
        if (merge_nodes(edge.first, edge.second)) {
            merge_count++;
        }
    }

    if (start == end) {
        if (queries[start].type == 3) {
            if (find_parent(queries[start].u) == find_parent(queries[start].v)) {
                cout << 1 << "\n";
            } else {
                cout << 0 << "\n";
            }
        }
    } else {
        int mid = (start + end) / 2;
        solve(node * 2, start, mid);
        solve(node * 2 + 1, mid + 1, end);
    }

    rollback(merge_count);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    map<pair<int, int>, int> edge_start;

    for (int i = 1; i <= M; ++i) {
        cin >> queries[i].type >> queries[i].u >> queries[i].v;
        if (queries[i].u > queries[i].v) swap(queries[i].u, queries[i].v);

        pair<int, int> e = {queries[i].u, queries[i].v};

        if (queries[i].type == 1) {
            edge_start[e] = i;
        } else if (queries[i].type == 2) {
            add_edge_to_tree(1, 1, M, edge_start[e], i - 1, e);
            edge_start.erase(e);
        }
    }

    for (auto& p : edge_start) {
        add_edge_to_tree(1, 1, M, p.second, M, p.first);
    }

    init_dsu(N);
    solve(1, 1, M);

    return 0;
}