// 16192(Voronoi Diagram Returns) 문제 : https://www.acmicpc.net/problem/16192
// 알고리즘 태그 목록
/*
브루트포스 알고리즘
기하학
보로노이 다이어그램
*/
#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
};

inline int get_distance_sq(const Point& a, const Point& b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<Point> sites(n);
    for (int i = 0; i < n; i++) {
        cin >> sites[i].x >> sites[i].y;
    }

    for (int i = 0; i < q; i++) {
        Point query;
        cin >> query.x >> query.y;

        int min_distance = 2e9;
        int count = 0;
        int id1 = -1, id2 = -1;

        for (int j = 0; j < n; j++) {
            int current_distance = get_distance_sq(query, sites[j]);

            if (current_distance < min_distance) {
                min_distance = current_distance;
                count = 1;
                id1 = j + 1;
            } 
            else if (current_distance == min_distance) {

                count++;
                if (count == 2) {
                    id2 = j + 1;
                }
            }
        }

        if (count == 1) {
            cout << "REGION " << id1 << "\n";
        } else if (count == 2) {
            cout << "LINE " << id1 << " " << id2 << "\n";
        } else {
            cout << "POINT" << "\n";
        }
    }

    return 0;
}