// 11866(요세푸스 문제 0) 문제 : https://www.acmicpc.net/problem/11866
// 알고리즘 태그 목록
/*
구현
자료 구조
큐
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    queue<int> q;

    for (int i = 1; i <= n; i++)
        q.push(i);

    cout << "<";

    while (!q.empty()) {
        for (int i = 0; i < k - 1; i++) {
            q.push(q.front());
            q.pop();
        }

        cout << q.front();
        q.pop();

        if (!q.empty())
            cout << ", ";
    }

    cout << ">" << "\n";

    return 0;
}