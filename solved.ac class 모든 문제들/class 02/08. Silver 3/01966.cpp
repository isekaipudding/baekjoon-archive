// 1966(프린터 큐) 문제 : https://www.acmicpc.net/problem/1966
// 알고리즘 태그 목록
/*
구현
자료 구조
시뮬레이션
큐
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--) {
        int n, m;
        cin >> n >> m;

        queue<pair<int, int>> q;

        priority_queue<int> pq;

        for(int i = 0; i < n; i++) {
            int priority;
            cin >> priority;
            q.push({priority, i});
            pq.push(priority);
        }

        int print_order = 0;

        while (!q.empty()) {
            int current_priority = q.front().first;
            int current_index = q.front().second;
            q.pop();

            if (current_priority == pq.top()) {
                print_order++;
                pq.pop();

                if (current_index == m) {
                    cout << print_order << "\n";
                    break;
                }
            } else {
                q.push({current_priority, current_index});
            }
        }
    }

    return 0;
}