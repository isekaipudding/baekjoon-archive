// 10746(Fencing the Herd) 문제 : https://www.acmicpc.net/problem/10746
// 알고리즘 태그 목록
/*
기하학
이분 탐색
집합과 맵
볼록 껍질
제곱근 분할법
*/
#include <bits/stdc++.h>

using namespace std;

static inline long long readLong() {
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

    long long x = 0;
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
    long long x, y;
    Point() : x(0), y(0) {}
    Point(long long x, long long y) : x(x), y(y) {}
    
    Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }
    Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
    Point operator*(long long c) const { return Point(x * c, y * c); }
    
    bool operator<(const Point& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
    bool operator==(const Point& o) const { 
        return x == o.x && y == o.y; 
    }
};

inline long long cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

inline long long cross(Point a, Point b, Point c) {
    return cross(b - a, c - a);
}

inline long long dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

inline long long dist2(Point a, Point b) {
    return dot(a - b, a - b);
}

Point pivot;

bool angleCmp(Point a, Point b) {
    long long c = cross(pivot, a, b);
    if (c == 0) return dist2(pivot, a) < dist2(pivot, b);
    return c > 0;
}

void unwind(vector<Point>& P, Point a) {
    int sz = P.size();
    while (sz > 1 && cross(P[sz - 2], P[sz - 1], a) <= 0) {
        --sz;
    }
    P.resize(sz);
}

vector<Point> get_hull(vector<Point> P) {
    if (P.empty()) return P;
    swap(P[0], *min_element(P.begin(), P.end()));
    pivot = P[0];
    sort(P.begin() + 1, P.end(), angleCmp);

    vector<Point> ret;
    ret.push_back(pivot);
    for (size_t i = 1; i < P.size(); i++) {
        unwind(ret, P[i]);
        ret.push_back(P[i]);
    }
    if (ret.size() > 2) unwind(ret, pivot);
    return ret;
}

bool radial_compare(Point x, Point y, Point base = Point(1, 0)) {
    long long cx = cross(base, x);
    long long cy = cross(base, y);
    if (cx == 0) cx = dot(base, x);
    if (cy == 0) cy = dot(base, y);
    if ((cx < 0) == (cy < 0)) return cross(Point(0, 0), x, y) > 0;
    return cy < 0;
}

long long convex_max_dot(const vector<Point>& P, Point pt) {
    int lo = 0;
    int hi = P.size() - 1;
    Point base = P[0] - P.back();
    Point rotated_pt(-pt.y, pt.x);
    
    while (lo < hi) {
        int md = (lo + hi + 1) / 2;
        Point v = P[md] - (md ? P[md - 1] : P.back());

        if (radial_compare(v, rotated_pt, base)) {
            lo = md;
        } else {
            hi = md - 1;
        }
    }
    return dot(P[lo], pt);
}

struct DynamicHull {
    vector<vector<Point>> hulls;

    void add(Point pt) {
        vector<Point> p = {pt};
        for (size_t i = 0; i < hulls.size(); i++) {
            if (hulls[i].empty()) {
                hulls[i] = get_hull(p);
                return;
            }
            for (Point point : hulls[i]) {
                p.push_back(point);
            }
            hulls[i].clear();
        }
        hulls.push_back(get_hull(p));
    }

    long long max_dot(Point pt) {
        long long ret = 0;
        bool init = false;
        for (size_t i = 0; i < hulls.size(); i++) {
            if (hulls[i].empty()) continue;
            long long res = convex_max_dot(hulls[i], pt);
            if (!init || res > ret) {
                init = true;
                ret = res;
            }
        }
        return ret;
    }

    bool empty() {
        return hulls.empty();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = readLong();
    int Q = readLong();

    if (N == 0 && Q == 0) return 0;

    vector<Point> h0_points;
    for (int i = 0; i < N; i++) {
        long long x = readLong();
        long long y = readLong();
        h0_points.push_back(Point(x, y));
    }
    vector<Point> h0 = get_hull(h0_points);

    DynamicHull h;
    for (int i = 0; i < Q; i++) {
        int cmd = readLong();
        if (cmd == 1) {
            long long x = readLong();
            long long y = readLong();
            h.add(Point(x, y));
        } else {
            long long a = readLong();
            long long b = readLong();
            long long c = readLong();
            Point pt(a, b);
            Point neg_pt(-a, -b);
            
            long long min_val = min(dot(h0[0], pt), -convex_max_dot(h0, neg_pt));
            if (!h.empty()) {
                min_val = min(min_val, -h.max_dot(neg_pt));
            }

            long long max_val = max(dot(h0[0], pt), convex_max_dot(h0, pt));
            if (!h.empty()) {
                max_val = max(max_val, h.max_dot(pt));
            }

            if (min_val <= c && max_val >= c) {
                printf("NO\n");
            } else {
                printf("YES\n");
            }
        }
    }

    return 0;
}