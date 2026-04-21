// 1259(팰린드롬수) 문제 : https://www.acmicpc.net/problem/1259
// 알고리즘 태그 목록
/*
구현
문자열
*/
#include <bits/stdc++.h>

using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string n;

    while (cin >> n) {
        if(n == "0") break;

        string original = n;
        
        reverse(n.begin(), n.end());
        
        if (original == n) {
            cout << "yes" << '\n';
        } else {
            cout << "no" << '\n';
        }
    }

    return 0;
}