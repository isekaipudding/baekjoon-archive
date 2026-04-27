// 16115(팬이에요) 문제 : https://www.acmicpc.net/problem/16115
// 알고리즘 태그 목록
/*
정렬
기하학
각도 정렬
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

using ll = long long;
using ld = long double;

// 거리를 비교할 때는 오차 방지를 위해 제곱값을 사용 (long long)
struct Point {
    ll x, y;
    ll distSqrt;
    ld angle;
};

int main() {
    // 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Point> points(N);
    ll maxDistSqrt = 0;

    for (int i = 0; i < N; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].distSqrt = points[i].x * points[i].x + points[i].y * points[i].y;
        if (points[i].distSqrt > maxDistSqrt) {
            maxDistSqrt = points[i].distSqrt;
        }
    }

    // 최대 거리에 있는 점들의 각도만 수집
    vector<ld> angles;
    const ld PI = acos(-1.0L);

    for (int i = 0; i < N; i++) {
        if (points[i].distSqrt == maxDistSqrt) {
            // atan2l은 (-PI, PI] 범위의 값을 반환
            angles.push_back(atan2l(points[i].y, points[i].x));
        }
    }

    // 각도 정렬
    sort(angles.begin(), angles.end());

    // 최대 각도 간격 찾기
    ld maxGap = 0;
    int size = angles.size();

    if (size == 1) {
        // 최대 거리에 점이 하나뿐이라면 한 바퀴를 다 돌려야 함
        maxGap = 2.0L * PI;
    } else {
        for (int i = 0; i < size; i++) {
            ld gap;
            if (i == size - 1) {
                // 마지막 각도와 첫 번째 각도 사이의 간격 (360도 회전 고려)
                gap = (2.0L * PI + angles[0]) - angles[i];
            } else {
                gap = angles[i + 1] - angles[i];
            }
            if (gap > maxGap) maxGap = gap;
        }
    }

    // 라디안을 도(degree)로 변환 (180 / PI 곱하기)
    ld result = maxGap * 180.0L / PI;

    cout << fixed << setprecision(10) << result << "\n";

    return 0;
}