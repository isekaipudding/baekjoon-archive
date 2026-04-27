// 16493(최대 페이지 수) 문제 : https://www.acmicpc.net/problem/16493
// 알고리즘 태그 목록
/*
다이나믹 프로그래밍
브루트포스 알고리즘
배낭 문제
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 N : 남은 기간 (배낭의 용량)
 M : 챕터의 수 (아이템의 개수)
 */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // dp[i] : i일 동안 읽을 수 있는 최대 페이지 수
    // N이 최대 200이므로 1차원 배열로 충분함
    vector<int> dp(N + 1, 0);

    for (int i = 0; i < M; i++) {
        int days, pages;
        cin >> days >> pages;

        // 뒤에서부터 갱신하여 현재 챕터가 중복 계산되는 것을 방지 (0/1 Knapsack)
        for (int j = N; j >= days; --j) {
            dp[j] = max(dp[j], dp[j - days] + pages);
        }
    }

    // N일 이내에 읽을 수 있는 최대 페이지 수 출력
    cout << dp[N] << "\n";

    return 0;
}