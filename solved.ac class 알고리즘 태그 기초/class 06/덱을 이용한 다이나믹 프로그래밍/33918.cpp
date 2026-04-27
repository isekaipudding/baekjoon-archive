// 33918(맛있는 스콘 만들기) 문제 : https://www.acmicpc.net/problem/33918
// 알고리즘 태그 목록
/*
다이나믹 프로그래밍
자료 구조
덱
덱을 이용한 구간 최댓값 트릭
덱을 이용한 다이나믹 프로그래밍
*/
#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <algorithm>

using namespace std;

// 도달할 수 없는 상태를 표시하기 위한 아주 작은 값
const int INF = 1e9; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, C, D;
    cin >> N >> M >> C >> D;

    vector<int> b(N);
    for (int i = 0; i < N; i++) {
        cin >> b[i];
    }

    // DP 배열 선언 (메모리 절약을 위해 prev, curr 2개만 1차원 배열로 교차 사용)
    vector<int> prev_dp(M + 1, -INF);
    vector<int> curr_dp(M + 1, -INF);

    // [Base Case] t = 0 일 때의 초기화
    for (int j = 1; j <= M; j++) {
        prev_dp[j] = M - abs(b[0] - j);
    }

    // 좌우로 탐색 가능한 최대 칸의 개수
    int K = D / C;

    // [DP State Trresultitions] t = 1 부터 N-1 까지
    for (int t = 1; t < N; t++) {
        // 배열 초기화
        fill(curr_dp.begin(), curr_dp.end(), -INF);

        // 1. 나머지가 같은 그룹(r)끼리 묶어서 독립적으로 덱 최적화 수행
        for (int r = 1; r <= C; r++) {
            vector<int> seq;
            // seq 배열에는 실제로 방문하는 온도(j)들이 들어감
            for (int j = r; j <= M; j += C) {
                seq.push_back(j);
            }

            int L = seq.size();
            if (L == 0) continue;

            deque<int> dq; // 유망한 인덱스를 저장할 단조 덱
            int right_ptr = 0;

            for (int i = 0; i < L; i++) {
                // [Step 1] 윈도우의 오른쪽을 확장 (최대 i + K까지 포함)
                while (right_ptr < L && right_ptr <= i + K) {
                    int val = prev_dp[seq[right_ptr]];
                    // 덱의 뒤(Back)에서부터 나보다 작거나 같은 값들은 의미 없으므로 제거
                    while (!dq.empty() && prev_dp[dq.back()] <= val) {
                        dq.pop_back();
                    }
                    // 현재 인덱스를 덱에 추가
                    dq.push_back(seq[right_ptr]);
                    right_ptr++;
                }

                // [Step 2] 윈도우의 왼쪽 범위를 벗어난 인덱스 제거 (seq[i] - D 미만)
                while (!dq.empty() && dq.front() < seq[i] - D) {
                    dq.pop_front();
                }

                // [Step 3] 덱의 맨 앞(Front)에 있는 값이 현재 윈도우 내의 최댓값
                // 유효한 이전 상태가 있다면 현재 상태를 갱신
                if (!dq.empty() && prev_dp[dq.front()] != -INF) {
                    curr_dp[seq[i]] = prev_dp[dq.front()] + M - abs(b[t] - seq[i]);
                }
            }
        }
        // 다음 시간을 위해 prev_dp를 curr_dp로 업데이트
        prev_dp = curr_dp;
    }

    // 모든 시각(N-1)이 끝난 후 완성된 맛의 최댓값 찾기
    int result = -INF;
    for (int j = 1; j <= M; j++) {
        result = max(result, prev_dp[j]);
    }

    cout << result << "\n";

    return 0;
}