// 2749(피보나치 수 3) 문제 : https://www.acmicpc.net/problem/2749
// 알고리즘 태그 목록
/*
수학
분할 정복을 이용한 거듭제곱
피사노 주기
*/
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD = 1000000;

ll pisano_period(ll m) {
    ll a = 0, b = 1;
    for (ll i = 0; i < m * m; i++) {
        ll temp = (a + b) % m;
        a = b;
        b = temp;
        if (a == 0 && b == 1) return i + 1;
    }
    return -1;
}

int dp[1500005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    ll period = pisano_period(MOD);

    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i < period; i++) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
    }

    cout << dp[n % period] << "\n";

    return 0;
}