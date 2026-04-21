// 2475(검증수) 문제 : https://www.acmicpc.net/problem/2475
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

    int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;

    cout << (a * a + b * b + c * c + d * d + e * e) % 10;
 
    return 0;
}