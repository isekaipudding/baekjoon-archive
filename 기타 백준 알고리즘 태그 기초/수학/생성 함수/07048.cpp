// 7048(Sweets) 문제 : https://www.acmicpc.net/problem/7048
// 알고리즘 태그 목록
/*
수학
다이나믹 프로그래밍
조합론
생성 함수
*/
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const int MOD = 2004;

ll get_combination(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r;

    vector<ll> numerator(r);
    for (ll i = 0; i < r; ++i) numerator[i] = n - i;

    for (ll i = 1; i <= r; ++i) {
        ll den = i;
        for (ll &num : numerator) {
            ll common = __gcd(num, den);
            num /= common;
            den /= common;
            if (den == 1) break;
        }
    }

    ll res = 1;
    for (ll num : numerator) {
        res = (res * (num % MOD)) % MOD;
    }
    return res;
}

ll get_prefix_sum(int limit, int n, const vector<int>& m) {
    if (limit < 0) return 0;
    ll total = 0;

    for (int i = 0; i < (1 << n); ++i) {
        ll weight = 0;
        int selected_count = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                weight += (m[j] + 1);
                selected_count++;
            }
        }

        ll term = get_combination(limit - weight + n, n);

        if (selected_count & 1) {
            total = (total - term + MOD) % MOD;
        } else {
            total = (total + term) % MOD;
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    while (cin >> n >> a >> b) {
        vector<int> m(n);
        for (int i = 0; i < n; ++i) cin >> m[i];

        ll result = (get_prefix_sum(b, n, m) - get_prefix_sum(a - 1, n, m) + MOD) % MOD;
        cout << result << "\n";
    }

    return 0;
}