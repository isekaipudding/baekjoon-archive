// 17459(Fruit Tree) 문제 : https://www.acmicpc.net/problem/17459
// 알고리즘 태그 목록
/*
자료 구조
트리
세그먼트 트리
이분 탐색
최소 공통 조상
희소 배열
퍼시스턴트 세그먼트 트리
보이어–무어 다수결 투표
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250005;
const int LOG = 19;

int N, Q;
int color[MAXN];
vector<int> graph[MAXN];

int depth[MAXN];
int parent_node[MAXN][LOG];
pair<int, int> up[MAXN][LOG];

int in_time[MAXN];
int out_time[MAXN];
int timer_count = 0;

vector<pair<int, int>> events[MAXN];

// 보이어-무어 다수결 투표 병합 함수
// 여기서 해당 알고리즘이 사용됩니다.
pair<int, int> merge_bm(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) return {a.first, a.second + b.second};
    if (a.second > b.second) return {a.first, a.second - b.second};
    return {b.first, b.second - a.second};
}

void dfs(int u, int p, int d) {
    in_time[u] = ++timer_count;
    depth[u] = d;
    parent_node[u][0] = p;
    up[u][0] = {color[u], 1};

    events[color[u]].push_back({in_time[u], 1});

    for (int i = 1; i < LOG; i++) {
        int prev_p = parent_node[u][i - 1];
        parent_node[u][i] = parent_node[prev_p][i - 1];
        up[u][i] = merge_bm(up[u][i - 1], up[prev_p][i - 1]);
    }

    for (int v : graph[u]) {
        if (v != p) dfs(v, u, d + 1);
    }
    
    out_time[u] = ++timer_count;
    events[color[u]].push_back({out_time[u], -1});
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 0; i < LOG; i++) {
        if ((diff >> i) & 1) u = parent_node[u][i];
    }
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        if (parent_node[u][i] != parent_node[v][i]) {
            u = parent_node[u][i];
            v = parent_node[v][i];
        }
    }
    return parent_node[u][0];
}

int count_to_root(int u, int C) {
    if (u == 0 || C == 0 || events[C].empty()) return 0;
    int target = in_time[u];
    
    auto it = upper_bound(events[C].begin(), events[C].end(), target,
        [](int val, const pair<int, int>& p) {
            return val < p.first;
        });
        
    if (it == events[C].begin()) return 0;
    --it;
    return it->second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> Q;

    for (int i = 1; i <= N; i++) cin >> color[i];

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    depth[0] = 0;
    for(int i = 0; i < LOG; i++) {
        parent_node[0][i] = 0;
        up[0][i] = {0, 0};
    }

    dfs(1, 0, 1);

    for (int c = 1; c <= N; c++) {
        int sum = 0;
        for (auto& ev : events[c]) {
            sum += ev.second;
            ev.second = sum;
        }
    }

    for (int q = 0; q < Q; q++) {
        int u, v;
        cin >> u >> v;
        int lca = get_lca(u, v);
        int path_len = depth[u] + depth[v] - 2 * depth[lca] + 1;

        pair<int, int> cand_state = {0, 0};

        int curr_u = u;
        int diff_u = depth[u] - depth[lca] + 1;
        for (int i = 0; i < LOG; i++) {
            if ((diff_u >> i) & 1) {
                cand_state = merge_bm(cand_state, up[curr_u][i]);
                curr_u = parent_node[curr_u][i];
            }
        }

        int curr_v = v;
        int diff_v = depth[v] - depth[lca];
        for (int i = 0; i < LOG; i++) {
            if ((diff_v >> i) & 1) {
                cand_state = merge_bm(cand_state, up[curr_v][i]);
                curr_v = parent_node[curr_v][i];
            }
        }

        int cand = cand_state.first;
        if (cand == 0) {
            cout << -1 << "\n";
            continue;
        }

        int count_u = count_to_root(u, cand);
        int count_v = count_to_root(v, cand);
        int count_lca = count_to_root(lca, cand);
        int count_p_lca = count_to_root(parent_node[lca][0], cand);

        int total_cand = count_u + count_v - count_lca - count_p_lca;

        if (total_cand * 2 > path_len) {
            cout << cand << "\n";
        } else {
            cout << -1 << "\n";
        }
    }

    return 0;
}