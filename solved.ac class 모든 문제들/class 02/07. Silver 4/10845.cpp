// 10845(큐) 문제 : https://www.acmicpc.net/problem/10845
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

    while(n--) {
        string cmd;
        cin >> cmd;

        if (cmd == "push") {
            int x;
            cin >> x;
            q.push(x);
        } 
        else if (cmd == "pop") {
            if (q.empty()) {
                cout << -1 << "\n";
            } else {
                cout << q.front() << "\n";
                q.pop();
            }
        } 
        else if (cmd == "size") {
            cout << q.size() << "\n";
        } 
        else if (cmd == "empty") {
            cout << (q.empty() ? 1 : 0) << "\n";
        } 
        else if (cmd == "front") {
            if (q.empty()) {
                cout << -1 << "\n";
            } else {
                cout << q.front() << "\n";
            }
        } 
        else if (cmd == "back") {
            if (q.empty()) {
                cout << -1 << "\n";
            } else {
                cout << q.back() << "\n";
            }
        }
    }

    return 0;
}