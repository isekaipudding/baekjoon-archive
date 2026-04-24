// 14565(역원(Inverse) 구하기) 문제 : https://www.acmicpc.net/problem/14565
// 알고리즘 태그 목록
/*
수학
정수론
모듈로 곱셈 역원
확장 유클리드 호제법
*/
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll extGCD(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    
    ll x1, y1;
    ll g = extGCD(b, a % b, x1, y1);
    
    x = y1;
    y = x1 - (a / b) * y1;
    
    return g;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, A;
    cin >> N >> A;

    ll addInv = N - A;

    ll x, y;
    ll gcd = extGCD(A, N, x, y);

    ll mulInv = -1;
    
    if (gcd == 1) {
        mulInv = (x % N + N) % N; 
    }

    cout << addInv << " " << mulInv << "\n";

    return 0;
}