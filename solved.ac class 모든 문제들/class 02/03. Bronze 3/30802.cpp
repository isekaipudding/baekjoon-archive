// 30802(웰컴 키트) 문제 : https://www.acmicpc.net/problem/30802
// 알고리즘 태그 목록
/*
수학
구현
사칙연산
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int c[6];
    for(int i = 0; i < 6; i++) cin >> c[i];

    int t, p;
    cin >> t >> p;

    int t_set = 0;
    for(int i = 0; i < 6; i++) t_set += (c[i] + t - 1) / t;

    cout << t_set << '\n';
    cout << n / p << " " << n % p;

    return 0;
}