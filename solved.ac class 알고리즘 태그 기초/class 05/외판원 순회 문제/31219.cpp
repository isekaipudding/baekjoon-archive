// 31219(세계 일주) 문제 : https://www.acmicpc.net/problem/31219
// 알고리즘 태그 목록
/*
브루트포스 알고리즘
기하학
백트래킹
선분 교차 판정
외판원 순회 문제
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// 좌표를 저장할 구조체
struct Point {
    double x, y;
};

int n;
vector<Point> points;
vector<bool> visited;
double min_dist = 1e18; // 충분히 큰 값으로 초기화

/**
 * 두 점 사이의 거리를 계산하는 함수
 */
double get_distance(Point a, Point b) {
    // hypot() 함수는 sqrt(dx*dx + dy*dy) 대신 hypot(x, y)로 유클리드 거리를 구해줍니다.
    return hypot(a.x - b.x, a.y - b.y);
}

/**
 * 백트래킹을 이용한 TSP 탐색
 * @param curr 현재 위치한 도시 인덱스
 * @param count 현재까지 방문한 도시 수
 * @param total_dist 현재까지 누적된 거리
 */
void backtracking(int curr, int count, double total_dist) {
    // 모든 도시를 다 방문했을 경우
    if (count == n) {
        // 마지막 도시에서 시작점(0번)으로 돌아가는 거리 추가
        double final_dist = total_dist + get_distance(points[curr], points[0]);
        if (final_dist < min_dist) {
            min_dist = final_dist;
        }
        return;
    }

    // 가지치기: 현재 거리가 이미 최솟값보다 크면 중단
    if (total_dist >= min_dist) return;

    for (int next = 0; next < n; ++next) {
        if (!visited[next]) {
            visited[next] = true;
            backtracking(next, count + 1, total_dist + get_distance(points[curr], points[next]));
            visited[next] = false; // 상태 복구 (백트래킹)
        }
    }
}

int main() {
    // 1. 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    points.resize(n);
    visited.assign(n, false);

    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    // 2. 예외 처리 : 도시가 2개 이하인 경우 순회 불가능
    if (n <= 2) {
        cout << -1 << "\n";
        return 0;
    }

    // 3. 0번 도시에서 출발 (시작점 고정)
    visited[0] = true;
    backtracking(0, 1, 0.0);

    // 4. 결과 출력 (소수점 6자리 고정)
    cout << fixed << setprecision(6) << min_dist << "\n";

    return 0;
}