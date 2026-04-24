// 17303(슈퍼브 다트) 문제 : https://www.acmicpc.net/problem/17303
// 알고리즘 태그 목록
/*
자료 구조
그래프 이론
기하학
분리 집합
다각형의 넓이
평면 그래프
이중 연결 요소
쌍대 그래프
*/
#include <bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
};

struct HalfEdge {
    int to;
    int id;
    int dir;
    int reverse_index;
    bool visited;
};

vector<Point> pts;
Point current_origin;

Point get_diff(int to) { 
    return Point{pts[to].x - current_origin.x, pts[to].y - current_origin.y}; 
}

int half(Point p) { 
    return p.y > 0 || (p.y == 0 && p.x > 0) ? 0 : 1; 
}

bool compare(const HalfEdge& a, const HalfEdge& b) {
    Point da = get_diff(a.to);
    Point db = get_diff(b.to);
    if (half(da) != half(db)) return half(da) < half(db);
    return (da.x * db.y - da.y * db.x) > 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    pts.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> pts[i].x >> pts[i].y;
    }

    vector<vector<HalfEdge>> graph(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back({v, i, 0, -1, false});
        graph[v].push_back({u, i, 1, -1, false});
    }

    for (int u = 1; u <= N; u++) {
        current_origin = pts[u];
        sort(graph[u].begin(), graph[u].end(), compare);
    }

    vector<vector<pair<int, int>>> edge_position(M, vector<pair<int, int>>(2));
    for (int u = 1; u <= N; u++) {
        for (int i = 0; i < (int)graph[u].size(); i++) {
            edge_position[graph[u][i].id][graph[u][i].dir] = {u, i};
        }
    }

    for (int u = 1; u <= N; u++) {
        for (int i = 0; i < (int)graph[u].size(); i++) {
            int id = graph[u][i].id;
            int dir = graph[u][i].dir;
            int opp_dir = 1 - dir;
            graph[u][i].reverse_index = edge_position[id][opp_dir].second;
        }
    }

    vector<long long> valid_areas;

    for (int u = 1; u <= N; u++) {
        for (int i = 0; i < (int)graph[u].size(); i++) {
            if (graph[u][i].visited) continue;

            long long area2 = 0;
            int start_u = u;
            int start_index = i;
            
            int current_u = u;
            int current_index = i;

            do {
                graph[current_u][current_index].visited = true;
                int next_u = graph[current_u][current_index].to;
                
                area2 += (pts[current_u].x * pts[next_u].y - pts[current_u].y * pts[next_u].x);
                
                int reverse_index = graph[current_u][current_index].reverse_index;
                int degree = graph[next_u].size();

                int next_index = (reverse_index - 1 + degree) % degree;
                
                current_u = next_u;
                current_index = next_index;
            } while (current_u != start_u || current_index != start_index);

            if (area2 > 0) {
                valid_areas.push_back(area2);
            }
        }
    }

    sort(valid_areas.begin(), valid_areas.end());

    cout << valid_areas.size() << "\n";
    cout << fixed << setprecision(1); 
    for (long long a : valid_areas) {
        cout << (a / 2.0) << "\n";
    }

    return 0;
}