// 7568(덩치) 문제 : https://www.acmicpc.net/problem/7568
// 알고리즘 태그 목록
/*
구현
브루트포스 알고리즘
*/
#include <bits/stdc++.h>

using namespace std;

pair<int, int> p[50];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for(int i = 0; i < n; i++) cin >> p[i].first >> p[i].second;

    for(int i = 0; i < n; i++) {
        int rank = 1;
        
        for(int j = 0; j < n; j++) {
            if (i == j) continue;

            if (p[j].first > p[i].first && p[j].second > p[i].second) {
                rank++;
            }
        }

        cout << rank << (i == n - 1 ? "" : " ");
    }

    return 0;
}