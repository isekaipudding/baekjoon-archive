// 2609(최대공약수와 최소공배수) 문제 : https://www.acmicpc.net/problem/2609
// 알고리즘 태그 목록
/*
수학
정수론
유클리드 호제법
*/
#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    cout << gcd(a, b) << '\n';
    cout << lcm(a, b) << '\n';

    return 0;
}