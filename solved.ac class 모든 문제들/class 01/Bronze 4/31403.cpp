// 31403(A + B - C) 문제 : https://www.acmicpc.net/problem/31403
// 알고리즘 태그 목록
/*
수학
문자열
사칙연산
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A, B, C;
    cin >> A >> B >> C;

    cout << stoi(A) + stoi(B) - stoi(C) << '\n';
    cout << stoi(A + B) - stoi(C) << '\n';

    return 0;
}