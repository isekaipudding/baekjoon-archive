// 18353(병사 배치하기) 문제 : https://www.acmicpc.net/problem/18353
// 알고리즘 태그 목록
/*
다이나믹 프로그래밍
가장 긴 증가하는 부분 수열 문제
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 입출력 성능 최적화
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> power(n);
    for (int i = 0; i < n; ++i) {
        cin >> power[i];
    }

    // dp[i]: i번째 병사를 마지막으로 하는 감소하는 부분 수열의 최대 길이
    vector<int> dp(n, 1);

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            // 앞선 병사의 전투력이 더 높을 때만 수열 연장 가능
            if (power[j] > power[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    // 가장 긴 부분 수열의 길이를 찾음
    int max_lds = 0;
    for (int i = 0; i < n; ++i) {
        max_lds = max(max_lds, dp[i]);
    }

    // 열외해야 하는 병사의 최소 수 출력
    cout << n - max_lds << "\n";

    return 0;
}