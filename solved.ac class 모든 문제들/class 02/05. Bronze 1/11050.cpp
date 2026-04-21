// 11050(이항 계수 1) 문제 : https://www.acmicpc.net/problem/11050
// 알고리즘 태그 목록
/*
수학
구현
조합론
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, r;
    cin >> n >> r;

    int result = 1;

    for(int i = 0; i < r; i++) result = result * (n - i) / (i + 1);

    cout << result;

    return 0;
}