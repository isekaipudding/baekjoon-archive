// 12022(짝) 문제 : https://www.acmicpc.net/problem/12022
// 알고리즘 태그 목록
/*
그래프 이론
안정 결혼 문제
*/
#include <bits/stdc++.h>

using namespace std;

int n;
int man_pref[501][501];
int woman_rank[501][501];
int next_proposal[501];
int wife[501];
int husband[501];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> man_pref[i][j];
        }
        next_proposal[i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int man;
            cin >> man;
            woman_rank[i][man] = j;
        }
    }

    queue<int> free_men;
    for (int i = 1; i <= n; i++) free_men.push(i);

    while (!free_men.empty()) {
        int m = free_men.front();
        free_men.pop();

        int w = man_pref[m][next_proposal[m]++];

        if (husband[w] == 0) {
            husband[w] = m;
            wife[m] = w;
        } else {
            int current_m = husband[w];
            if (woman_rank[w][m] < woman_rank[w][current_m]) {
                wife[current_m] = 0;
                free_men.push(current_m);

                husband[w] = m;
                wife[m] = w;
            } else {
                free_men.push(m);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << wife[i] << "\n";
    }

    return 0;
}