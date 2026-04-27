// 5582(공통 부분 문자열) 문제 : https://www.acmicpc.net/problem/5582
// 알고리즘 태그 목록
/*
다이나믹 프로그래밍
문자열
최장 공통 부분 수열 문제
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 4001 x 4001 배열은 스택 영역을 초과할 수 있으므로 전역 변수나 vector를 사용합니다.
int dp[4001][4001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    cin >> s1 >> s2;

    int n1 = s1.length();
    int n2 = s2.length();
    int lcs_result = 0;

    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            // 두 문자가 같으면 대각선 위(이전 연속 길이) 값에 1을 더함
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                lcs_result = max(lcs_result, dp[i][j]);
            } else {
                // 연속성이 깨지면 0으로 초기화
                dp[i][j] = 0;
            }
        }
    }

    cout << lcs_result << "\n";

    return 0;
}