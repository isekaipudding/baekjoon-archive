// 10451(순열 사이클) 문제 : https://www.acmicpc.net/problem/10451
// 알고리즘 태그 목록
/*
그래프 이론
그래프 탐색
순열 사이클 분할
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int> p(N + 1);
        vector<bool> visited(N + 1, false);

        for (int i = 1; i <= N; i++) {
            cin >> p[i];
        }

        int cycle_count = 0;

        for (int i = 1; i <= N; i++) {
            if (!visited[i]) {
                cycle_count++;
                int current = i;

                while (!visited[current]) {
                    visited[current] = true;
                    current = p[current];
                }
            }
        }

        cout << cycle_count << "\n";
    }

    return 0;
}