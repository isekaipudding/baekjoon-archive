// 4949(균형잡힌 세상) 문제 : https://www.acmicpc.net/problem/4949
// 알고리즘 태그 목록
/*
자료 구조
문자열
스택
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    while (true) {
        getline(cin, s);

        if (s == ".") break;

        vector<char> v;
        bool isBalanced = true;

        for (char c : s) {
            if (c == '(' || c == '[') {
                v.push_back(c);
            }
            else if (c == ')') {
                if (v.empty() || v.back() != '(') {
                    isBalanced = false;
                    break;
                }
                v.pop_back();
            }
            else if (c == ']') {
                if (v.empty() || v.back() != '[') {
                    isBalanced = false;
                    break;
                }
                v.pop_back();
            }
        }

        if (isBalanced && v.empty()) {
            cout << "yes" << "\n";
        } else {
            cout << "no" << "\n";
        }
    }

    return 0;
}