// 10869(사칙연산) 문제 : https://www.acmicpc.net/problem/10869
// 알고리즘 태그 목록
/*
구현
사칙연산
수학
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    cout << a + b << '\n';
    cout << a - b << '\n';
    cout << a * b << '\n';
    cout << a / b << '\n';
    cout << a % b << '\n';
 
    return 0;
}