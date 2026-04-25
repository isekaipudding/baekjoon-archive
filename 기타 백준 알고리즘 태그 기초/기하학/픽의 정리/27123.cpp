// 27123(Electric Fence) 문제 : https://www.acmicpc.net/problem/27123
// 알고리즘 태그 목록
/*
수학
기하학
정수론
유클리드 호제법
픽의 정리
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll get_gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, p;
    cin >> n >> m >> p;

    ll double_area = p * m;

    ll b = p;
    b += get_gcd(n, m);
    b += get_gcd(abs(n - p), m);

    ll result = (double_area - b + 2) / 2;

    cout << result << endl;

    return 0;
}