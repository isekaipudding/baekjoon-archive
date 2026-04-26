// 15792(A/B - 2) 문제 : https://www.acmicpc.net/problem/15792
// 알고리즘 태그 목록
/*
수학
구현
사칙연산
임의 정밀도 / 큰 수 연산
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A, B;
    cin >> A >> B;

    cout << A / B;
    cout << ".";

    int remainder = A % B;
    
    for (int i = 0; i <= 1000; ++i) {
        if (remainder == 0) break;

        remainder *= 10;
        cout << remainder / B;
        remainder %= B;
    }

    cout << "\n";

    return 0;
}