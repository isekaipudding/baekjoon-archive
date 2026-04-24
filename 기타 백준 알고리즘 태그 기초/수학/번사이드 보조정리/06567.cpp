// 6567(Let it Bead) 문제 : https://www.acmicpc.net/problem/6567
// 알고리즘 태그 목록
/*
수학
브루트포스 알고리즘
조합론
번사이드 보조정리
*/
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll power(ll base, ll exponent) {
    ll result = 1;
    for (int i = 0; i < exponent; i++) result *= base;
    return result;
}

ll burnside(ll c, ll n) {
    ll total_fixed_points = 0;

    for (int i = 0; i < n; i++) {
        total_fixed_points += power(c, gcd(i, n));
    }

    if (n & 1) {
        total_fixed_points += n * power(c, (n + 1) / 2);
    } else {
        total_fixed_points += (n / 2) * power(c, n / 2 + 1);
        total_fixed_points += (n / 2) * power(c, n / 2);
    }

    return total_fixed_points / (2 * n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll c, n;
    while (cin >> c >> n && (c != 0 || n != 0)) {
        if (n == 0) {
            cout << 0 << "\n";
            continue;
        }
        cout << burnside(c, n) << "\n";
    }

    return 0;
}