// 1688(지민이의 테러) 문제 : https://www.acmicpc.net/problem/1688
// 알고리즘 태그 목록
/*
기하학
선분 교차 판정
오목 다각형 내부의 점 판정
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
};

int ccw(Point a, Point b, Point c) {
    ll result = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (result > 0) return 1;  // 반시계
    if (result < 0) return -1; // 시계
    return 0;                  // 일직선
}

bool onSegment(Point a, Point b, Point p) {
    if (ccw(a, b, p) == 0) {
        return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
               min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
    }
    return false;
}

int isInside(const vector<Point>& poly, Point p) {
    int n = poly.size();
    int count = 0;

    for (int i = 0; i < n; i++) {
        Point a = poly[i];
        Point b = poly[(i + 1) % n];

        if (onSegment(a, b, p)) return 1;

        if ((a.y > p.y) != (b.y > p.y)) {
            double intersectX = (double)(b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x;
            if (p.x < intersectX) {
                count++;
            }
        }
    }
    return count % 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    
    vector<Point> polygon(N);
    for (int i = 0; i < N; i++) {
        cin >> polygon[i].x >> polygon[i].y;
    }

    for (int i = 0; i < 3; i++) {
        Point person;
        cin >> person.x >> person.y;
        cout << isInside(polygon, person) << "\n";
    }

    return 0;
}