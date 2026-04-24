// 10262(주사위 게임) 문제 : https://www.acmicpc.net/problem/10262
// 알고리즘 태그 목록
/*
수학
구현
사칙연산
확률론
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;
    int gunnar_sum = a1 + b1 + a2 + b2;

    int a3, b3, a4, b4;
    cin >> a3 >> b3 >> a4 >> b4;
    int emma_sum = a3 + b3 + a4 + b4;

    if (gunnar_sum > emma_sum) {
        cout << "Gunnar" << "\n";
    } else if (emma_sum > gunnar_sum) {
        cout << "Emma" << "\n";
    } else {
        cout << "Tie" << "\n";
    }

    return 0;
}