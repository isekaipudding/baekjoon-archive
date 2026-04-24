// 해당 알고리즘이 필요한 백준 문제가 없으므로 직접 소스 코드를 만듭니다.
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// 거듭제곱 연산 (a^b % m)
ll pow_mod(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = (__int128)res * a % m;
        a = (__int128)a * a % m;
        b >>= 1;
    }
    return res;
}

// 확장 유클리드 호제법 (ax + by = gcd(a, b))
ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    ll x1, y1;
    ll gcd = extended_gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

// 원시근 찾기 (소수 m에 대해)
ll find_primitive_root(ll m) {
    if (m == 2) return 1;
    vector<ll> factors;
    ll phi = m - 1;
    ll n = phi;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) factors.push_back(n);

    for (ll res = 2; res <= m; res++) {
        bool ok = true;
        for (ll f : factors) {
            if (pow_mod(res, phi / f, m) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return res;
    }
    return -1;
}

// 이산 로그 해결 : g^z = a (mod m) -> BSGS 알고리즘
ll baby_step_giant_step(ll g, ll a, ll m) {
    if (a == 1) return 0;
    ll n = (ll)sqrt(m) + 1;
    map<ll, ll> baby_steps;
    
    // Baby-step : g^j % m 저장
    for (ll j = 0; j < n; j++) {
        baby_steps[pow_mod(g, j, m)] = j;
    }

    // Giant-step : a * (g^-n)^i % m 확인
    ll gn = pow_mod(g, n * (m - 2) % (m - 1), m); // Fermat's Little Theorem for inverse
    ll cur = a;
    for (int i = 0; i < n; i++) {
        if (baby_steps.count(cur)) {
            return i * n + baby_steps[cur];
        }
        cur = (__int128)cur * gn % m;
    }
    return -1;
}

// 이산 k제곱근 구하기 : x^k = a (mod m)
ll discrete_kth_root(ll k, ll a, ll m) {
    if (a == 0) return 0;
    
    ll g = find_primitive_root(m);
    ll z = baby_step_giant_step(g, a, m);
    if (z == -1) return -1; // 해 없음

    // 선형 합동식 : y * k = z (mod m-1)
    ll y, temp_x;
    ll phi = m - 1;
    ll gcd = extended_gcd(k, phi, y, temp_x);

    if (z % gcd != 0) return -1; // 해 없음

    // 특수해 구하기
    y = (__int128)y * (z / gcd) % (phi / gcd);
    if (y < 0) y += (phi / gcd);

    return pow_mod(g, y, m);
}

int main() {
    ll k, a, m;
    cout << "x^k = a (mod m) 형태의 값을 입력하세요 (k a m): ";
    cin >> k >> a >> m;

    ll res = discrete_kth_root(k, a, m);
    if (res == -1) cout << "해를 찾을 수 없습니다." << endl;
    else cout << "x의 값 중 하나: " << res << endl;

    return 0;
}