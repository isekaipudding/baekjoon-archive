// 14675(단절점과 단절선) 문제 : https://www.acmicpc.net/problem/14675
// 알고리즘 태그 목록
/*
그래프 이론
애드 혹
트리
단절점과 단절선
*/
#include <iostream>
#include <vector>

using namespace std;

// 정점의 차수를 저장할 배열 (최대 100,000개)
int degree[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // N-1개의 간선 정보를 읽으며 각 정점의 차수를 계산
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        degree[u]++;
        degree[v]++;
    }

    int Q;
    cin >> Q;
    while (Q--) {
        int t, k;
        cin >> t >> k;

        if (t == 1) {
            // 단절점 질의: 차수가 2 이상이면 단절점
            if (degree[k] >= 2) cout << "yes\n";
            else cout << "no\n";
        } 
        else if (t == 2) {
            // 단절선 질의: 트리의 모든 간선은 단절선
            cout << "yes\n";
        }
    }

    return 0;
}