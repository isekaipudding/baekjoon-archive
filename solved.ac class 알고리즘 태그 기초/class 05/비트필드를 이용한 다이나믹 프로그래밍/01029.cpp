// 1029(그림 교환) 문제 : https://www.acmicpc.net/problem/1029
// 알고리즘 태그 목록
/*
다이나믹 프로그래밍
비트마스킹
비트필드를 이용한 다이나믹 프로그래밍
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int n;
int price[15][15];
// dp[방문상태][현재소유자][구입가격] = 이후에 그림을 가질 수 있는 최대 인원수
int dp[1 << 15][15][10];

// 비트 DP를 이용한 탐색
// mask 현재까지 그림을 거쳐간 사람들의 비트마스크
// curr 현재 그림을 소유한 사람
// curr_price 현재 소유자가 그림을 샀을 때의 가격
int bitmast_dp(int mask, int curr, int curr_price) {
    // 이미 계산된 적이 있다면 반환 (메모이제이션)
    int& ret = dp[mask][curr][curr_price];
    if (ret != -1) return ret;

    // 최소한 현재 소유자 본인은 포함되므로 1로 시작
    ret = 1;

    for (int next = 0; next < n; ++next) {
        // 1. 아직 그림을 소유한 적이 없고
        // 2. 현재 소유자가 산 가격보다 비싸거나 같게 팔 수 있다면
        if (!(mask & (1 << next)) && price[curr][next] >= curr_price) {
            ret = max(ret, 1 + bitmast_dp(mask | (1 << next), next, price[curr][next]));
        }
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < n; ++j) {
            price[i][j] = s[j] - '0';
        }
    }

    // DP 테이블 초기화
    memset(dp, -1, sizeof(dp));

    // 0번(사장)이 그림을 가지고 시작 (방문상태: 1, 소유자: 0, 가격: 0)
    cout << bitmast_dp(1, 0, 0) << "\n";

    return 0;
}