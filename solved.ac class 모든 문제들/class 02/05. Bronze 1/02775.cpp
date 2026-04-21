// 2775(부녀회장이 될테야) 문제 : https://www.acmicpc.net/problem/2775
// 알고리즘 태그 목록
/*
수학
구현
다이나믹 프로그래밍
*/
#include <bits/stdc++.h>

using namespace std;

const int limit = 14;
int dp[15][15];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i <= limit; i++) dp[0][i] = i;

    for (int i = 1; i <= limit; i++) {
        for (int j = 1; j <= limit; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    int t;
    cin >> t;

    while(t--) {
        int k, n;
        cin >> k >> n;
        cout << dp[k][n] << '\n';
    }

    return 0;
}