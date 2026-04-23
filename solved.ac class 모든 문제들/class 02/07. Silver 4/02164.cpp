// 2164(카드2) 문제 : https://www.acmicpc.net/problem/2164
// 알고리즘 태그 목록
/*
자료 구조
큐
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    queue<int> q;
    for (int i = 1; i <= n; i++) q.push(i);

    while (q.size() > 1) {
        q.pop();

        int top = q.front();
        
        q.pop();
        q.push(top);
    }

    cout << q.front() << "\n";

    return 0;
}