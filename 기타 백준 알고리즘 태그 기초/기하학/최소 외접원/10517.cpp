// 10517(Radar Coverage) 문제 : https://www.acmicpc.net/problem/10517
// 알고리즘 태그 목록
/*
기하학
최소 외접원
*/
#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int t = 1; t <= N; ++t) {
        Point p[3];
        for (int i = 0; i < 3; i++) {
            cin >> p[i].x >> p[i].y;
        }

        Point center;
        bool found_center = false;

        for (int i = 0; i < 3; i++) {
            Point A = p[i];           // 현재 각의 꼭짓점
            Point B = p[(i + 1) % 3]; // 다른 점 1
            Point C = p[(i + 2) % 3]; // 다른 점 2

            double dot = (B.x - A.x) * (C.x - A.x) + (B.y - A.y) * (C.y - A.y);

            if (dot <= 0) {
                center.x = (B.x + C.x) / 2.0;
                center.y = (B.y + C.y) / 2.0;
                found_center = true;
                break;
            }
        }

        if (!found_center) {
            double x1 = p[0].x, y1 = p[0].y;
            double x2 = p[1].x, y2 = p[1].y;
            double x3 = p[2].x, y3 = p[2].y;

            double D = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
            center.x = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / D;
            center.y = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / D;
        }

        cout << "Case #" << t << ": " << fixed << setprecision(2) << center.x << " " << center.y << "\n";
    }

    return 0;
}