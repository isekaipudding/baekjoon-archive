// 11568(민균이의 계략) 문제 : https://www.acmicpc.net/problem/11568
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
    // 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> cards(n);
    for (int i = 0; i < n; ++i) {
        cin >> cards[i];
    }

    // dp[i]: cards[i]를 마지막 원소로 하는 LIS의 길이
    vector<int> dp(n, 1);
    int max_lis = 1;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            // 현재 카드보다 작은 앞선 카드가 있다면 수열 연장 가능
            if (cards[j] < cards[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        // 전체 수열 중 최댓값 갱신
        if (dp[i] > max_lis) {
            max_lis = dp[i];
        }
    }

    cout << max_lis << "\n";

    return 0;
}