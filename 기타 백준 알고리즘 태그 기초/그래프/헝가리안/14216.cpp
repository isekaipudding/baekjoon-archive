// 14216(할 일 정하기 2) 문제 : https://www.acmicpc.net/problem/14216
// 알고리즘 태그 목록
/*
헝가리안
*/
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> cost_matrix(N + 1, vector<int>(N + 1));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> cost_matrix[i][j];
        }
    }

    vector<int> lx(N + 1, 0), ly(N + 1, 0);
    vector<int> match_y(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        vector<int> slack(N + 1, INF);
        vector<bool> visit_x(N + 1, false), visit_y(N + 1, false);
        vector<int> pre(N + 1, 0);

        int current_x = i, current_y = 0;
        match_y[0] = current_x;

        do {
            visit_y[current_y] = true;
            int x = match_y[current_y];
            int delta = INF;
            int next_y = 0;

            for (int y = 1; y <= N; y++) {
                if (!visit_y[y]) {
                    int currentrent_slack = cost_matrix[x][y] - lx[x] - ly[y];
                    if (currentrent_slack < slack[y]) {
                        slack[y] = currentrent_slack;
                        pre[y] = current_y;
                    }
                    if (slack[y] < delta) {
                        delta = slack[y];
                        next_y = y;
                    }
                }
            }

            for (int y = 0; y <= N; y++) {
                if (visit_y[y]) {
                    lx[match_y[y]] += delta;
                    ly[y] -= delta;
                } else {
                    slack[y] -= delta;
                }
            }
            current_y = next_y;
        } while (match_y[current_y] != 0);

        while (current_y != 0) {
            int prev_y = pre[current_y];
            match_y[current_y] = match_y[prev_y];
            current_y = prev_y;
        }
    }

    int total_min_cost = 0;
    for (int y = 1; y <= N; y++) {
        if (match_y[y] > 0) {
            total_min_cost += cost_matrix[match_y[y]][y];
        }
    }

    cout << total_min_cost << "\n";

    return 0;
}