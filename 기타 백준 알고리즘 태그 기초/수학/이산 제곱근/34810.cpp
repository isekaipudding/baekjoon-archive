// 34810(월향 가설 (Large)) 문제 : https://www.acmicpc.net/problem/34810
// 알고리즘 태그 목록
/*
수학
정수론
무작위화
페르마의 소정리
이산 제곱근
*/
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll power(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;
    while (b > 0) {
        if (b % 2 == 1) res = (__int128)res * a % m;
        a = (__int128)a * a % m;
        b /= 2;
    }
    return res;
}

ll modSqrt(ll a, ll p) {
    a %= p;
    if (a == 0) return 0;
    if (p == 2) return a;
    
    if (power(a, (p - 1) / 2, p) != 1) return -1;

    if (p % 4 == 3) return power(a, (p + 1) / 4, p);

    ll s = 0, q = p - 1;
    while (q % 2 == 0) {
        q /= 2;
        s++;
    }

    ll z = 2;
    while (power(z, (p - 1) / 2, p) != p - 1) z++;

    ll m = s;
    ll c = power(z, q, p);
    ll t = power(a, q, p);
    ll r = power(a, (q + 1) / 2, p);

    while (t != 0 && t != 1) {
        ll temp_t = t;
        ll i = 0;
        for (i = 1; i < m; i++) {
            temp_t = (__int128)temp_t * temp_t % p;
            if (temp_t == 1) break;
        }
        
        ll b = power(c, 1LL << (m - i - 1), p);
        m = i;
        c = (__int128)b * b % p;
        t = (__int128)t * c % p;
        r = (__int128)r * b % p;
    }

    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        ll a, p;
        cin >> a >> p;

        ll result = modSqrt(a, p);

        if (result == -1) {
            cout << "0" << "\n";
        } else {
            ll x1 = result;
            ll x2 = p - result;
            if (x1 > x2) swap(x1, x2);
            
            if (x1 == x2) cout << x1 << "\n";
            else cout << x1 << " " << x2 << "\n";
        }
    }

    return 0;
}