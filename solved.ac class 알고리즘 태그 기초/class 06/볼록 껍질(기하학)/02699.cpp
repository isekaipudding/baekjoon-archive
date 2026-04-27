// 2699(격자점 컨벡스헐) 문제 : https://www.acmicpc.net/problem/2699
// 알고리즘 태그 목록
/*
기하학
볼록 껍질
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

// 점의 정보를 저장할 구조체
struct Point {
    ll x, y;
};

// CCW (Counter Clockwise) 함수: 세 점의 방향성을 결정
// 결과 > 0: 반시계, 결과 < 0: 시계, 결과 = 0: 일직선
ll ccw(Point a, Point b, Point c) {
    ll res = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (res > 0) return 1;
    if (res < 0) return -1;
    return 0;
}

// 두 점 사이의 거리의 제곱 (정렬 시 거리를 비교하기 위함)
ll dist(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void solve() {
    int n;
    cin >> n;

    vector<Point> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    // 1. 기준점 찾기 (Y가 크고, X가 작은 순)
    int start = 0;
    for (int i = 1; i < n; i++) {
        if (p[i].y > p[start].y || (p[i].y == p[start].y && p[i].x < p[start].x)) {
            start = i;
        }
    }
    swap(p[0], p[start]);

    // 2. 기준점 제외 나머지 점들을 시계 방향으로 정렬
    sort(p.begin() + 1, p.end(), [&](const Point& a, const Point& b) {
        ll res = ccw(p[0], a, b);
        if (res != 0) return res < 0; // 시계 방향(-1)인 것이 우선
        return dist(p[0], a) < dist(p[0], b);
    });

    // 3. Graham Scan 알고리즘 수행
    vector<Point> hull;
    for (int i = 0; i < n; i++) {
        // 현재 점이 시계 방향이 아니면(CCW >= 0) 이전 점을 제거
        while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), p[i]) >= 0) {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }

    // 4. 결과 출력
    cout << hull.size() << "\n";
    for (const auto& pt : hull) {
        cout << pt.x << " " << pt.y << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }

    return 0;
}