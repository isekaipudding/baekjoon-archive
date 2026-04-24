// 1199(오일러 경로) 문제 : https://www.acmicpc.net/problem/1199
// 알고리즘 태그 목록
/*
그래프 이론
그래프 탐색
집합과 맵
깊이 우선 탐색
오일러 경로
*/
#include <bits/stdc++.h>

using namespace std;

int graph[1001][1001];
int current_neighbor[1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++) {
        int row_sum = 0;
        for (int j = 1; j <= N; j++) {
            cin >> graph[i][j];
            row_sum += graph[i][j];
        }
        if (row_sum & 1) {
            cout << -1 << "\n";
            return 0;
        }
        current_neighbor[i] = 1;
    }

    vector<int> stack;
    stack.push_back(1);

    while (!stack.empty()) {
        int current = stack.back();
        bool found = false;

        for (int &next = current_neighbor[current]; next <= N; next++) {
            if (graph[current][next] > 0) {
                graph[current][next]--;
                graph[next][current]--;
                stack.push_back(next);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << current << " ";
            stack.pop_back();
        }
    }

    return 0;
}