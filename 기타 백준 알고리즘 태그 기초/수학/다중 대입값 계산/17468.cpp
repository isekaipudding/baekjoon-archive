// 17468(N! mod P (3)) 문제 : https://www.acmicpc.net/problem/17468
// 알고리즘 태그 목록
/*
수학
정수론
분할 정복을 이용한 거듭제곱
제곱근 분할법
고속 푸리에 변환
다중 대입값 계산
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef __int128_t lll;
typedef long double ld;

const ld PI = acos(-1.0L);

struct Complex {
    ld r, i;
    Complex(ld r = 0, ld i = 0) : r(r), i(i) {}
    Complex operator+(const Complex& o) const { return {r + o.r, i + o.i}; }
    Complex operator-(const Complex& o) const { return {r - o.r, i - o.i}; }
    Complex operator*(const Complex& o) const { return {r * o.r - i * o.i, r * o.i + i * o.r}; }
    Complex conj() const { return {r, -i}; }
};

void fft(vector<Complex>& a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    static vector<Complex> roots;
    static int last_n = -1;
    if (last_n != n) {
        roots.resize(n / 2);
        for (int i = 0; i < n / 2; i++) {
            ld ang = 2.0L * PI * i / n;
            roots[i] = Complex(cos(ang), sin(ang));
        }
        last_n = n;
    }
    for (int len = 2; len <= n; len <<= 1) {
        int step = n / len;
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < len / 2; j++) {
                Complex w = roots[step * j];
                if (invert) w.i = -w.i;
                Complex u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
            }
        }
    }
    if (invert) for (auto& x : a) { x.r /= (ld)n; x.i /= (ld)n; }
}

vector<ll> multiply(const vector<ll>& a, const vector<ll>& b, ll m) {
    int n = 1;
    int target = (int)a.size() + (int)b.size() - 1;
    while (n < target) n <<= 1;

    vector<Complex> fa(n), fb(n);
    for (int i = 0; i < (int)a.size(); i++) fa[i] = Complex((ld)(a[i] & 131071), (ld)(a[i] >> 17));
    for (int i = 0; i < (int)b.size(); i++) fb[i] = Complex((ld)(b[i] & 131071), (ld)(b[i] >> 17));

    fft(fa, false); fft(fb, false);

    vector<Complex> r0(n), r1(n);
    for (int i = 0; i < n; i++) {
        int j = (n - i) & (n - 1);
        Complex aL = (fa[i] + fa[j].conj()) * Complex(0.5, 0);
        Complex aH = (fa[i] - fa[j].conj()) * Complex(0, -0.5);
        Complex bL = (fb[i] + fb[j].conj()) * Complex(0.5, 0);
        Complex bH = (fb[i] - fb[j].conj()) * Complex(0, -0.5);
        r0[i] = aL * bL + (aL * bH + aH * bL) * Complex(0, 1);
        r1[i] = aH * bH;
    }

    fft(r0, true); fft(r1, true);

    vector<ll> res(target);
    for (int i = 0; i < target; i++) {
        ll m0 = (ll)(r0[i].r + 0.5L) % m;
        ll m1 = (ll)(r0[i].i + 0.5L) % m;
        ll m2 = (ll)(r1[i].r + 0.5L) % m;
        lll val = (lll)m0 + (((lll)m1 << 17) % m) + (((lll)m2 << 34) % m);
        res[i] = (ll)(val % m);
        if (res[i] < 0) res[i] += m;
    }
    return res;
}

ll power(ll a, ll b, ll m) {
    ll res = 1; a %= m;
    while (b > 0) {
        if (b & 1) res = (lll)res * a % m;
        a = (lll)a * a % m;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N, P;
    if (!(cin >> N >> P)) return 0;
    if (N >= P) { cout << 0 << "\n"; return 0; }
    if (N == 0) { cout << 1 << "\n"; return 0; }

    ll D = 1;
    while (D * (D + 1) < N) D <<= 1;

    int max_size = (int)(4 * D + 5);
    vector<ll> fact(max_size, 1), invF(max_size, 1);
    for (int i = 1; i < max_size; i++) fact[i] = (lll)fact[i - 1] * i % P;
    invF[max_size - 1] = power(fact[max_size - 1], P - 2, P);
    for (int i = max_size - 2; i >= 0; i--) invF[i] = (lll)invF[i + 1] * (i + 1) % P;

    vector<ll> inv_n(max_size);
    for (int i = 1; i < max_size; i++) inv_n[i] = (lll)fact[i - 1] * invF[i] % P;

    vector<ll> f = {1, 2};
    ll d = 1;
    // 이 while문 안에 있는 것이 바로 다중 대입값 계산!
    while (d < D) {
        vector<ll> g(d + 1);
        for (int i = 0; i <= d; i++) {
            g[i] = (lll)f[i] * invF[i] % P * invF[d - i] % P;
            if ((d - i) & 1) g[i] = (P - g[i]) % P;
        }
        vector<ll> B_slice(inv_n.begin() + 1, inv_n.begin() + (4 * d + 2));
        vector<ll> C = multiply(g, B_slice, P);
        vector<ll> h(4 * d + 2);
        for (int i = 0; i <= d; i++) h[i] = f[i];
        for (int i = d + 1; i < 4 * d + 2; i++) {
            h[i] = (lll)C[i - 1] * fact[i] % P * invF[i - d - 1] % P;
        }
        f.resize(2 * d + 1);
        for (int i = 0; i <= 2 * d; i++) f[i] = (lll)h[2 * i] * h[2 * i + 1] % P;
        d <<= 1;
    }

    ll result = 1, index = 0;
    while ((index + 1) * D <= N) {
        result = (lll)result * f[index] % P;
        index++;
    }
    for (ll j = index * D + 1; j <= N; j++) result = (lll)result * j % P;
    cout << (ll)result << "\n";
    return 0;
}