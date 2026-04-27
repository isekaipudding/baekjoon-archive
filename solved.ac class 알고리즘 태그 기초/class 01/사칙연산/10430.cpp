// 10430(나머지) 문제 : https://www.acmicpc.net/problem/10430
// 알고리즘 태그 목록
/*
수학
구현
사칙연산
*/
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c;

    cin >> a >> b >> c;

    cout << (a + b) % c << '\n';
    cout << ((a % c) + (b % c)) % c << '\n';
    cout << (a * b) % c << '\n';
    cout << ((a % c) * (b % c)) % c << '\n';

    return 0;
}