// 16746(Four-Coloring) 문제 : https://www.acmicpc.net/problem/16746
// 알고리즘 태그 목록
/*
그래프 이론
애드 혹
해 구성하기
평면 그래프
*/
#include <bits/stdc++.h>

using namespace std;

static inline int readInt() {
    static char buf[1 << 20];
    static int ptr = 0;
    static int len = 0;
    auto getChar = [&]() -> char {
        if (ptr == len) {
            len = fread(buf, 1, 1 << 20, stdin);
            ptr = 0;
            if (len == 0) return EOF;
        }
        return buf[ptr++];
    };
    int x = 0;
    char c = getChar();
    while (c != EOF && c != '-' && (c < '0' || c > '9')) c = getChar();
    if (c == EOF) return 0;
    bool neg = false;
    if (c == '-') { neg = true; c = getChar(); }
    for (; c >= '0' && c <= '9'; c = getChar()) {
        x = x * 10 + (c - '0');
    }
    return neg ? -x : x;
}

struct Point {
    int x, y, id;
    bool operator<(const Point& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

int get_dir(int sx, int sy, int nx, int ny) {
    if (nx < sx && ny > sy) return 0;
    if (nx < sx && ny == sy) return 1;
    if (nx < sx && ny < sy) return 2;
    if (nx == sx && ny < sy) return 3;
    return -1; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = readInt();
    int M = readInt();

    vector<Point> pts(N + 1);
    for (int i = 1; i <= N; i++) {
        pts[i].x = readInt();
        pts[i].y = readInt();
        pts[i].id = i;
    }

    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        int u = readInt();
        int v = readInt();
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<Point> sorted_pts = pts;
    sorted_pts.erase(sorted_pts.begin()); 
    sort(sorted_pts.begin(), sorted_pts.end());

    vector<int> color(N + 1, 0);
    vector<bool> visited(N + 1, false);

    for (const auto& p : sorted_pts) {
        int curr = p.id;
        int u[4] = {-1, -1, -1, -1};
        bool present[5] = {false, false, false, false, false};
        
        for (int nxt : adj[curr]) {
            if (color[nxt] != 0) {
                int dir = get_dir(pts[curr].x, pts[curr].y, pts[nxt].x, pts[nxt].y);
                if (dir != -1) {
                    u[dir] = nxt;
                    present[color[nxt]] = true;
                }
            }
        }
        
        int distinct_colors = 0;
        for (int c = 1; c <= 4; c++) {
            if (present[c]) distinct_colors++;
        }
        
        if (distinct_colors < 4) {
            for (int c = 1; c <= 4; c++) {
                if (!present[c]) {
                    color[curr] = c;
                    break;
                }
            }
        } 
        else {
            int c0 = color[u[0]];
            int c1 = color[u[1]];
            int c2 = color[u[2]];
            int c3 = color[u[3]];
            
            vector<int> comp;
            int head = 0;
            comp.push_back(u[0]);
            visited[u[0]] = true;
            bool found_u2 = false;
            
            while (head < comp.size()) {
                int v = comp[head++];
                if (v == u[2]) found_u2 = true;
                for (int nxt : adj[v]) {
                    if (!visited[nxt] && (color[nxt] == c0 || color[nxt] == c2)) {
                        visited[nxt] = true;
                        comp.push_back(nxt);
                    }
                }
            }
            
            for (int v : comp) visited[v] = false;
            
            if (!found_u2) {
                for (int v : comp) {
                    color[v] = (color[v] == c0) ? c2 : c0;
                }
                color[curr] = c0;
            } 
            else {
                comp.clear();
                head = 0;
                comp.push_back(u[1]);
                visited[u[1]] = true;
                
                while (head < comp.size()) {
                    int v = comp[head++];
                    for (int nxt : adj[v]) {
                        if (!visited[nxt] && (color[nxt] == c1 || color[nxt] == c3)) {
                            visited[nxt] = true;
                            comp.push_back(nxt);
                        }
                    }
                }
                
                for (int v : comp) visited[v] = false;
                
                for (int v : comp) {
                    color[v] = (color[v] == c1) ? c3 : c1;
                }
                color[curr] = c1;
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        cout << color[i] << "\n";
    }

    return 0;
}