// 13701(중복 제거) 문제 : https://www.acmicpc.net/problem/13701
// 알고리즘 태그 목록
/*
비트마스킹
비트 집합
*/
#include <bits/stdc++.h>

using namespace std;

bitset<33554432> bs; // 1 << 25 = 33554432

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while(cin >> n) {
        if (!bs.test(n)) {
            cout << n << ' ';
            bs.set(n);
        }
    }

    return 0;
}