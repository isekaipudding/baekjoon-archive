// 29266(Делоне) 문제 : https://www.acmicpc.net/problem/29266
// 알고리즘 태그 목록
/*
기하학
보로노이 다이어그램
델로네 삼각분할
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
};

struct Edge {
    int u, v, tri_index, opp_index;
    bool operator<(const Edge& other) const {
        if (u != other.u) return u < other.u;
        return v < other.v;
    }
};

struct Triangle {
    int v[3];
};

ll get_ccw(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool check_is_inside(Point a, Point b, Point c, Point d) {
    ll adx = a.x - d.x, ady = a.y - d.y;
    ll bdx = b.x - d.x, bdy = b.y - d.y;
    ll cdx = c.x - d.x, cdy = c.y - d.y;

    __int128 det = (__int128)(adx * adx + ady * ady) * (bdx * cdy - cdx * bdy)
                 - (__int128)(bdx * bdx + bdy * bdy) * (adx * cdy - cdx * ady)
                 + (__int128)(cdx * cdx + cdy * cdy) * (adx * bdy - bdx * ady);

    return det > 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<Point> p(n + 1);
        vector<bool> used(n + 1, false);
        for (int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y;

        vector<Triangle> tris(m);
        vector<Edge> edges;
        edges.reserve(m * 3);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < 3; j++) {
                cin >> tris[i].v[j];
                used[tris[i].v[j]] = true;
            }

            if (get_ccw(p[tris[i].v[0]], p[tris[i].v[1]], p[tris[i].v[2]]) < 0) {
                swap(tris[i].v[1], tris[i].v[2]);
            }

            for (int j = 0; j < 3; j++) {
                int u = tris[i].v[j];
                int v = tris[i].v[(j + 1) % 3];
                int opp = tris[i].v[(j + 2) % 3];
                edges.push_back({min(u, v), max(u, v), i, opp});
            }
        }

        bool possible = true;

        for (int i = 1; i <= n; i++) {
            if (!used[i]) {
                possible = false;
                break;
            }
        }

        if (possible) {
            sort(edges.begin(), edges.end());

            for (int i = 0; i < (int)edges.size() - 1; i++) {
                if (edges[i].u == edges[i + 1].u && edges[i].v == edges[i + 1].v) {
                    int t_index = edges[i].tri_index;
                    Point A = p[tris[t_index].v[0]];
                    Point B = p[tris[t_index].v[1]];
                    Point C = p[tris[t_index].v[2]];
                    Point D = p[edges[i + 1].opp_index];

                    // 
                    if (check_is_inside(A, B, C, D)) {
                        possible = false;
                        break;
                    }
                }
            }
        }

        if (possible) cout << "YES" << "\n";
        else cout << "NO" << "\n";
    }

    return 0;
}