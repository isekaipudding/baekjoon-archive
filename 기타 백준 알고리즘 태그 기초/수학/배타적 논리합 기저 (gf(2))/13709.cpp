// 13709(XOR 합 2) 문제 : https://www.acmicpc.net/problem/13709
// 알고리즘 태그 목록
/*
수학
선형대수학
가우스 소거법
배타적 논리합 기저 (gf(2))
*/
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll basis[64];

void insert_basis(ll x) {
    for (int i = 62; i >= 0; i--) {

        if (!(x & (1LL << i))) continue;

        if (!basis[i]) {
            basis[i] = x;
            return;
        }

        x ^= basis[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        ll value;
        cin >> value;
        insert_basis(value);
    }

    ll max_xor = 0;

    for (int i = 62; i >= 0; i--) {
        if ((max_xor ^ basis[i]) > max_xor) {
            max_xor ^= basis[i];
        }
    }

    cout << max_xor << "\n";

    return 0;
}