// 1676(팩토리얼 0의 개수) 문제 : https://www.acmicpc.net/problem/1676
// 알고리즘 태그 목록
/*
수학
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int result = 0;

    while (n >= 5) {
        result += n / 5;
        n /= 5;
    }

    cout << result << "\n";

    return 0;
}