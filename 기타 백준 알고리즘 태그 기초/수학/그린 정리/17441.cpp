// 17441(파리채 만들기) 문제 : https://www.acmicpc.net/problem/17441
// 알고리즘 태그 목록
/*
수학
기하학
미적분학
그린 정리
*/
#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

struct Point {
    ld x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Point> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }
    p.push_back(p[0]);

    ld area = 0;
    ld sum_x = 0, sum_y = 0;
    ld sum_x2 = 0, sum_y2 = 0;

    for (int i = 0; i < n; i++) {
        ld cross = p[i].x * p[i + 1].y - p[i + 1].x * p[i].y;
        
        area += cross;
        sum_x += (p[i].x + p[i + 1].x) * cross;
        sum_y += (p[i].y + p[i + 1].y) * cross;
        
        sum_x2 += (p[i].x * p[i].x + p[i].x * p[i + 1].x + p[i + 1].x * p[i + 1].x) * cross;
        sum_y2 += (p[i].y * p[i].y + p[i].y * p[i + 1].y + p[i + 1].y * p[i + 1].y) * cross;
    }

    area /= 2.0;
    ld bar_x = sum_x / (6.0 * area);
    ld bar_y = sum_y / (6.0 * area);

    ld ex2 = sum_x2 / (12.0 * area);
    ld ey2 = sum_y2 / (12.0 * area);

    ld var_sum = (ex2 - bar_x * bar_x) + (ey2 - bar_y * bar_y);

    cout << fixed << setprecision(10);
    cout << 2.0 * var_sum << "\n";

    return 0;
}