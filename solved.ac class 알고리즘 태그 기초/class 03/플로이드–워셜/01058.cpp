// 1058(친구) 문제 : https://www.acmicpc.net/problem/1058
// 알고리즘 태그 목록
/*
그래프 이론
브루트포스 알고리즘
그래프 탐색
최단 경로
플로이드-워셜
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// INF는 infinity의 줄임말
const int INF = 987654321;
// dist는 distance의 줄임말
int dist[51][51];

// 플로이드-워셜 알고리즘을 수행하는 독립적인 함수
void floyd(int n) {
    // k: 거쳐가는 지점 (경유지)
    for (int k = 0; k < n; k++) {
        // i: 출발 지점
        for (int i = 0; i < n; i++) {
            // j: 도착 지점
            for (int j = 0; j < n; j++) {
                // i에서 j로 바로 가는 것보다 k를 거쳐가는 것이 더 짧다면 갱신
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 1. 초기 거리 설정
    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (row[j] == 'Y') {
                dist[i][j] = 1;
            } else {
                dist[i][j] = INF;
            }
        }
    }

    // 2. 알고리즘 실행
    floyd(n);

    int max_friends = 0;

    // 3. 결과 도출 (2-친구 계산)
    for (int i = 0; i < n; ++i) {
        int count = 0;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            // 최단 거리가 2 이하인 모든 사람이 '2-친구'
            if (dist[i][j] <= 2) {
                count++;
            }
        }
        if (count > max_friends) {
            max_friends = count;
        }
    }

    cout << max_friends << "\n";

    return 0;
}