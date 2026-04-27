// 1197(최소 스패닝 트리) 문제 : https://www.acmicpc.net/problem/1197
// 알고리즘 태그 목록
/*
그래프 이론
최소 스패닝 트리
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 간선 정보를 저장할 구조체
struct Edge {
    int u, v, w;
    // 가중치 기준 오름차순 정렬을 위한 비교 연산자 정의
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

int parent[10001];

// Union-Find : Find 연산 (경로 압축 포함)
int find_parent(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find_parent(parent[x]);
}

// Union-Find : Union 연산
void union_parent(int a, int b) {
    a = find_parent(a);
    b = find_parent(b);
    if (a < b) parent[b] = a;
    else parent[a] = b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;

    // 1. 부모 노드 초기화
    for (int i = 1; i <= V; ++i) {
        parent[i] = i;
    }

    vector<Edge> edges(E);
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // 2. 간선을 가중치 기준으로 정렬 (O(E log E))
    sort(edges.begin(), edges.end());

    long long total_weight = 0;
    int edge_count = 0;

    // 3. 그리디하게 간선 선택
    for (int i = 0; i < E; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        // 사이클이 형성되지 않는 경우에만 선택 (부모가 다를 때)
        if (find_parent(u) != find_parent(v)) {
            union_parent(u, v);
            total_weight += w;
            edge_count++;
            
            // 트리의 성질 : 간선 개수가 V-1개가 되면 종료
            if (edge_count == V - 1) break;
        }
    }

    cout << total_weight << "\n";

    return 0;
}