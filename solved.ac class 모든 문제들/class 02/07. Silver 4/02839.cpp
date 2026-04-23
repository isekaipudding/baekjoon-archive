// 2839(설탕 배달) 문제 : https://www.acmicpc.net/problem/2839
// 알고리즘 태그 목록
/*
다이나믹 프로그래밍
그리디 알고리즘
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

    while(n >= 0) {
        if(n % 5 == 0) {
            result += n / 5;
            cout << result;
            return 0;
        }

        n -= 3;
        result++;
    }

    cout << -1;

    return 0;
}