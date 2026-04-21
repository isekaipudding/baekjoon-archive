// 10950(A+B - 3) 문제 : https://www.acmicpc.net/problem/10950
// 알고리즘 태그 목록
/*
구현
사칙연산
수학
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--) {
        int a, b;
        cin >> a >> b;
        cout << a + b << '\n';
    }

    return 0;
}