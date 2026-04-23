// 9012(괄호) 문제 : https://www.acmicpc.net/problem/9012
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

    int t;
    cin >> t;

    while(t--) {
        string s;
        cin >> s;

        int balance = 0;
        bool isVPS = true;

        for (char c : s) {
            if (c == '(')
                balance++;
            else {
                balance--;
                
                if (balance < 0) {
                    isVPS = false;
                    break;
                }
            }
        }
        if (isVPS && balance == 0) {
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }

    return 0;
}