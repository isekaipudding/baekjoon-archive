// 10828(스택) 문제 : https://www.acmicpc.net/problem/10828
// 알고리즘 태그 목록
/*
구현
자료 구조
스택
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> s;

    while(n--) {
        string cmd;
        cin >> cmd;

        if (cmd == "push") {
            int x;
            cin >> x;
            s.push_back(x);
        } 
        else if (cmd == "pop") {
            if (s.empty()) {
                cout << -1 << "\n";
            } else {
                cout << s.back() << "\n";
                s.pop_back();
            }
        } 
        else if (cmd == "size") {
            cout << s.size() << "\n";
        } 
        else if (cmd == "empty") {
            cout << (s.empty() ? 1 : 0) << "\n";
        } 
        else if (cmd == "top") {
            if (s.empty()) {
                cout << -1 << "\n";
            } else {
                cout << s.back() << "\n";
            }
        }
    }

    return 0;
}