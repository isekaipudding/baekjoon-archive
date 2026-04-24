// 10955(Potemkin cycle) 문제 : https://www.acmicpc.net/problem/10955
// 알고리즘 태그 목록
/*
그래프 이론
그래프 탐색
너비 우선 탐색
비트 집합
현 그래프
*/
#include <bits/stdc++.h>

using namespace std;

int n, m;

vector<vector<bool>> graph;
vector<vector<bool>> visited_state;
vector<vector<bool>> is_valid_edge;

stack<pair<int, int>> state_stack;
set<int> cycle_nodes;
bool cycle_found = false;

inline bool is_valid_transition(int u, int v, int w) {
    return !(graph[u][v] && graph[v][w] && graph[u][w]) && graph[v][w];
}

void find_state_cycle(pair<int, int> node) {
    if (cycle_found) return;
    
    state_stack.push(node);
    
    if (visited_state[node.first][node.second]) {
        // 사이클 발견
        cycle_nodes.insert(node.first);
        cycle_nodes.insert(node.second);
        state_stack.pop();
        
        while (!state_stack.empty()) {
            pair<int, int> current = state_stack.top();
            state_stack.pop();
            
            is_valid_edge[current.first][current.second] = true;
            is_valid_edge[current.second][current.first] = true;
            cycle_nodes.insert(current.first);
            cycle_nodes.insert(current.second);
            
            if (current == node) break;
        }
        cycle_found = true;
        return;
    }

    visited_state[node.first][node.second] = true;
    
    for (int next_node = 0; next_node < n; next_node++) {
        if (next_node == node.first) continue;
        
        if (is_valid_transition(node.first, node.second, next_node)) {
            find_state_cycle({node.second, next_node});
            if (cycle_found) return;
        }
    }

    if (!state_stack.empty()) state_stack.pop();
}

vector<bool> is_cycle_node;
vector<bool> visited_node;
stack<int> node_stack;
vector<int> final_cycle;

void extract_chordless_cycle(int current, int parent = -1) {
    if (cycle_found) return;
    
    node_stack.push(current);
    visited_node[current] = true;
    
    for (int next_node = 0; next_node < n; next_node++) {
        if (next_node == current || next_node == parent) continue;
        if (cycle_found) return;
        
        if (graph[current][next_node] && visited_node[next_node] && is_cycle_node[next_node] && !is_valid_edge[current][next_node]) {
            node_stack.pop();
            while (!node_stack.empty()) {
                int x = node_stack.top();
                node_stack.pop();
                final_cycle.push_back(x);
                if (x == next_node) break;
            }
            cycle_found = true;
            return;
        }

        if (is_valid_edge[current][next_node]) {
            if (visited_node[next_node]) {
                while (!node_stack.empty()) {
                    int x = node_stack.top();
                    node_stack.pop();
                    final_cycle.push_back(x);
                    if (x == next_node) break;
                }
                cycle_found = true;
            } else {
                extract_chordless_cycle(next_node, current);
            }
        }
        if (cycle_found) return;
    }
    
    if (!node_stack.empty()) node_stack.pop();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    graph.assign(n, vector<bool>(n, false));
    visited_state.assign(n, vector<bool>(n, false));
    is_valid_edge.assign(n, vector<bool>(n, false));

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; 
        graph[u][v] = true;
        graph[v][u] = true;
    }

    for (int i = 0; i < n; i++) {
        find_state_cycle({i, i});
    }

    if (!cycle_found) {
        cout << "no" << "\n";
        return 0;
    }

    is_cycle_node.assign(n, false);
    visited_node.assign(n, false);
    
    int start_node = 0;
    for (int node : cycle_nodes) {
        is_cycle_node[node] = true;
        start_node = node;
    }

    cycle_found = false; 
    extract_chordless_cycle(start_node);

    if (final_cycle.empty()) {
        cout << "no\n";
    } else {
        for (int v : final_cycle) {
            cout << v + 1 << " ";
        }
        cout << "\n";
    }

    return 0;
}