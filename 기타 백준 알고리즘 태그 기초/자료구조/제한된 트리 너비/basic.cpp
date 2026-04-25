// 해당 알고리즘이 필요한 백준 문제가 없으므로 직접 소스 코드를 만듭니다.
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

// Nice Tree Decomposition의 노드 타입
enum NodeType { LEAF = 0, INTRODUCE = 1, FORGET = 2, JOIN = 3 };

struct TreeNode {
    NodeType type;
    int v; // Introduce나 Forget에서 추가/제거되는 정점 번호
    vector<int> bag; // 현재 노드의 Bag에 포함된 정점 목록
    vector<int> children; // 자식 트리 노드들
};

struct BoundedTreeWidthDP {
    int n; 
    vector<int> weights; 
    vector<vector<int>> adj; 
    vector<TreeNode> td; 

    // dp[i][mask] : i번째 트리 노드에서, bag 안의 정점들의 선택 상태가 mask일 때의 최대 가중치
    vector<unordered_map<int, int>> dp;

    BoundedTreeWidthDP(int n, vector<int>& w, vector<vector<int>>& graph, vector<TreeNode>& tree_decomp) 
        : n(n), weights(w), adj(graph), td(tree_decomp) {
        dp.resize(td.size());
    }

    bool is_edge(int u, int v) {
        for (int nxt : adj[u]) {
            if (nxt == v) return true;
        }
        return false;
    }

    // 소스(src) bag의 마스크를 타겟(tgt) bag의 마스크 위치로 매핑
    // 만약 src의 정점이 tgt에 없다면 해당 비트는 무시됨 (Forget 노드에서 유용)
    int map_mask(int mask, const vector<int>& src, const vector<int>& tgt) {
        int res = 0;
        for (size_t i = 0; i < src.size(); ++i) {
            if (mask & (1 << i)) {
                for (size_t j = 0; j < tgt.size(); ++j) {
                    if (tgt[j] == src[i]) {
                        res |= (1 << j);
                        break;
                    }
                }
            }
        }
        return res;
    }

    void solve_dp(int curr) {
        for (int child : td[curr].children) {
            solve_dp(child);
        }

        auto& node = td[curr];
        int bag_size = node.bag.size();

        if (node.type == LEAF) {
            dp[curr][0] = 0;
        } 
        else if (node.type == INTRODUCE) {
            int child = node.children[0];
            int new_v = node.v;
            
            int new_v_idx = -1;
            for (int i = 0; i < bag_size; ++i) {
                if (node.bag[i] == new_v) new_v_idx = i;
            }

            // 수정: 구조적 바인딩 대신 pair 순회 사용
            for (auto& p : dp[child]) {
                int child_mask = p.first;
                int val = p.second;

                // 자식의 마스크를 현재 bag 순서에 맞게 변환
                int curr_mask = map_mask(child_mask, td[child].bag, node.bag);
                
                // 1. new_v를 선택하지 않는 경우
                dp[curr][curr_mask] = max(dp[curr][curr_mask], val);

                // 2. new_v를 선택하는 경우
                bool can_pick = true;
                for (int i = 0; i < bag_size; ++i) {
                    if (i == new_v_idx) continue;
                    if ((curr_mask & (1 << i)) && is_edge(node.bag[i], new_v)) {
                        can_pick = false;
                        break;
                    }
                }
                
                if (can_pick) {
                    int pick_mask = curr_mask | (1 << new_v_idx);
                    dp[curr][pick_mask] = max(dp[curr][pick_mask], val + weights[new_v]);
                }
            }
        } 
        else if (node.type == FORGET) {
            int child = node.children[0];
            
            // 수정: 구조적 바인딩 대신 pair 순회 사용
            for (auto& p : dp[child]) {
                int child_mask = p.first;
                int val = p.second;

                // map_mask가 타겟(curr)에 없는 forgot_v의 비트를 자동으로 날려줌
                int curr_mask = map_mask(child_mask, td[child].bag, node.bag);
                dp[curr][curr_mask] = max(dp[curr][curr_mask], val);
            }
        } 
        else if (node.type == JOIN) {
            int left = node.children[0];
            int right = node.children[1];

            // 자식들의 마스크를 현재 노드 기준의 마스크로 정렬
            unordered_map<int, int> mapped_left, mapped_right;
            
            // 수정: 구조적 바인딩 대신 pair 순회 사용
            for (auto& p : dp[left]) {
                int m = p.first, v = p.second;
                mapped_left[map_mask(m, td[left].bag, node.bag)] = max(mapped_left[map_mask(m, td[left].bag, node.bag)], v);
            }
            for (auto& p : dp[right]) {
                int m = p.first, v = p.second;
                mapped_right[map_mask(m, td[right].bag, node.bag)] = max(mapped_right[map_mask(m, td[right].bag, node.bag)], v);
            }

            for (auto& p : mapped_left) {
                int m = p.first;
                int val1 = p.second;

                if (mapped_right.count(m)) {
                    int val2 = mapped_right[m];
                    int overlap_weight = 0;
                    for (int i = 0; i < bag_size; ++i) {
                        if (m & (1 << i)) overlap_weight += weights[node.bag[i]];
                    }
                    dp[curr][m] = max(dp[curr][m], val1 + val2 - overlap_weight);
                }
            }
        }
    }

    int get_max_independent_set(int root) {
        solve_dp(root);
        int ans = 0;
        // 수정: 구조적 바인딩 대신 pair 순회 사용
        for (auto& p : dp[root]) {
            int val = p.second;
            ans = max(ans, val);
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, e;
    // 그래프 정점 수, 간선 수
    cin >> n >> e;

    vector<int> weights(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> weights[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < e; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int t, root;
    // 트리 분할의 노드 수, 루트 노드 번호
    cin >> t >> root;

    vector<TreeNode> td(t);
    for (int i = 0; i < t; ++i) {
        int type_val;
        // 타입(0:LEAF, 1:INTRO, 2:FORGET, 3:JOIN), 정점 v
        cin >> type_val >> td[i].v;
        td[i].type = static_cast<NodeType>(type_val);

        int bag_size;
        cin >> bag_size;
        td[i].bag.resize(bag_size);
        for (int j = 0; j < bag_size; ++j) {
            cin >> td[i].bag[j];
        }

        int num_children;
        cin >> num_children;
        td[i].children.resize(num_children);
        for (int j = 0; j < num_children; ++j) {
            cin >> td[i].children[j];
        }
    }

    BoundedTreeWidthDP solver(n, weights, adj, td);
    cout << solver.get_max_independent_set(root) << "\n";

    return 0;
}

/*
[예시 입력]
3 2
10 20 30
1 2
2 3
7 6
0 0 0 0
1 1 1 1 1 0
1 2 2 1 2 1 1
2 1 1 2 1 2
1 3 2 2 3 1 3
2 2 1 3 1 4
2 3 0 1 5
[예시 출력]
40
*/