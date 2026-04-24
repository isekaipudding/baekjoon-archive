// 11653(소인수분해) 문제 : https://www.acmicpc.net/problem/11653
// 알고리즘 태그 목록
/*
수학
정수론
소수 판정
소인수분해
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    if (N == 1) {
        return 0;
    }

    for (int i = 2; i * i <= N; ++i) {
        while (N % i == 0) {
            cout << i << "\n";
            N /= i;
        }
    }

    if (N > 1) {
        cout << N << "\n";
    }

    return 0;
}