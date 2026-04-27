// 2747(피보나치 수) 문제 : https://www.acmicpc.net/problem/2747
// 알고리즘 태그 목록
/*
수학
구현
다이나믹 프로그래밍
*/
#include <iostream>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // n의 최대 범위가 45이므로, 인덱스 n을 포함하기 위해 크기 46의 배열 선언
    ll dp[46];

    // 초기식
    dp[0] = 0;
    dp[1] = 1;

    // 점화식
    // Bottom-Up 방식으로 배열을 채워나감
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    // 결과 출력
    cout << dp[n] << '\n';

    return 0;
}