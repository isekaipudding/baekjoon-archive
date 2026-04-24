// 31217(Y) 문제 : https://www.acmicpc.net/problem/31217
// 알고리즘 태그 목록
/*
수학
그래프 이론
조합론
차수열
*/
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> degree(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        degree[u]++;
        degree[v]++;
    }

    long long total_y_shapes = 0;

    for (int i = 1; i <= n; i++) {
        if (degree[i] >= 3) {
            long long d = degree[i];

            long long combinations = d * (d - 1) * (d - 2) / 6;
            
            total_y_shapes = (total_y_shapes + combinations) % MOD;
        }
    }

    cout << total_y_shapes << "\n";

    return 0;
}