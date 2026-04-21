// 15829(Hashing) 문제 : https://www.acmicpc.net/problem/15829
// 알고리즘 태그 목록
/*
구현
문자열
해싱
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1234567891;

ll pow_mod(ll base, ll exponent) {
    ll result = 1;
    base %= MOD;
    while (exponent) {
        if (exponent & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exponent >>= 1;
    }
    return result;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int l;
    cin >> l;

    string s;
    cin >> s;

    ll result = 0;

    for(int i = 0; i < l; i++) {
        ll a = s[i] - 'a' + 1;

        ll term = (a * pow_mod(31, i)) % MOD;
        result = (result + term) % MOD;
    }

    cout << result;

    return 0;
}