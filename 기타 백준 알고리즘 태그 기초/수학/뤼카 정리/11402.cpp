// 11402(이항 계수 4) 문제 : https://www.acmicpc.net/problem/11402
// 알고리즘 태그 목록
/*
수학
다이나믹 프로그래밍
정수론
조합론
뤼카 정리
*/
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int dp[2005][2005];
int M;

void precompute() {
    for (int i = 0; i <= M; ++i) {
        dp[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % M;
        }
    }
}

int lucas(ll n, ll k) {
    if (k == 0) return 1;
    if (n == 0) return 0; 
    
    int ni = n % M;
    int ki = k % M;
    
    if (ni < ki) return 0;
    
    return (1LL * lucas(n / M, k / M) * dp[ni][ki]) % M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, K;
    cin >> N >> K >> M;

    precompute();

    cout << lucas(N, K) << "\n";

    return 0;
}