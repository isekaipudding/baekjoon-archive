// 16029(Fibonacci represultentations) 문제 : https://www.acmicpc.net/problem/16029
// 알고리즘 태그 목록
/*
수학
다이나믹 프로그래밍
자료 구조
트리
세그먼트 트리
집합과 맵
트리를 사용한 집합과 맵
레드-블랙 트리
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 7;
const int INF = 1e9;

// 2x2 행렬 구조체
struct Matrix {
    int d[2][2];

    Matrix() {
        memset(d, 0, sizeof(d));
    }

    void init(int k) {
        d[0][0] = 1; d[0][1] = 0;
        d[1][0] = k; d[1][1] = 1;
    }

    static Matrix mul(const Matrix& A, const Matrix& B) {
        Matrix result;
        result.d[0][0] = (1LL * A.d[0][0] * B.d[0][0] + 1LL * A.d[0][1] * B.d[1][0]) % MOD;
        result.d[0][1] = (1LL * A.d[0][0] * B.d[0][1] + 1LL * A.d[0][1] * B.d[1][1]) % MOD;
        result.d[1][0] = (1LL * A.d[1][0] * B.d[0][0] + 1LL * A.d[1][1] * B.d[1][0]) % MOD;
        result.d[1][1] = (1LL * A.d[1][0] * B.d[0][1] + 1LL * A.d[1][1] * B.d[1][1]) % MOD;
        return result;
    }
};

// 세그먼트 트리 구조체
struct SegmentTree {
    struct Node {
        Matrix m;
        int a, b;
        bool valid;

        Node() : a(0), b(0), valid(false) {}

        void init(const pii& v) {
            a = v.first;
            b = v.second;
            m.init((b - a) / 2);
            valid = false;
        }
    };

    int size;
    vector<Node> tree;

    SegmentTree(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.resize(2 * size);
    }

    void init_node(int i, const pii& v) {
        tree[i | size].init(v);
    }

    void toggle(int i) {
        i |= size;
        tree[i].valid = !tree[i].valid;

        for (i /= 2; i > 0; i /= 2) {
            const auto& lc = tree[2 * i];
            const auto& rc = tree[2 * i + 1];

            tree[i].valid = lc.valid | rc.valid;

            if (!lc.valid) {
                tree[i] = rc;
            } else if (!rc.valid) {
                tree[i] = lc;
            } else {
                tree[i].a = lc.a;
                tree[i].b = rc.b;
                
                int gap = rc.a - lc.b;
                tree[i].m.d[0][0] = 1; tree[i].m.d[0][1] = (gap - 1) / 2;
                tree[i].m.d[1][0] = 1; tree[i].m.d[1][1] = gap / 2;
                
                Matrix temp = Matrix::mul(lc.m, tree[i].m);
                tree[i].m = Matrix::mul(temp, rc.m);
            }
        }
    }

    int query() const {
        return (tree[1].m.d[0][0] + tree[1].m.d[0][1]) % MOD;
    }
};

// 젝켄도르프 정리(피보나치 진법) 관리 구조체
struct ZeckendorfManager {
    set<pii> intervals;
    vector<vector<pii>> event_log;
    int current_step;

    ZeckendorfManager(int n) {
        event_log.resize(n);
        current_step = 0;
        intervals.emplace(-INF, -INF); // 하한 센티널
        intervals.emplace(INF, INF);   // 상한 센티널
    }

    void add_interval(int a, int b) {
        if (a > b) return;
        intervals.emplace(a, b);
        event_log[current_step].emplace_back(a, b);
    }

    void remove_interval(set<pii>::iterator& p) {
        event_log[current_step].emplace_back(*p);
        intervals.erase(p);
    }

    void add_fib_out(int x) {
        auto r = intervals.lower_bound({x, x});
        auto l = prev(r);
        
        // C++17 구조적 바인딩 대신 명시적으로 first, second 할당
        int al = l->first;
        int bl = l->second;
        int ar = r->first;
        int br = r->second;

        if (bl + 1 == x) {
            remove_interval(l);
            add_interval(al, bl - 2);
            add_fib_out(x + 1);
        } else if (x + 1 == ar) {
            remove_interval(r);
            add_fib_out(br + 1);
        } else {
            int a = x, b = x;
            if (bl + 2 == x) { remove_interval(l); a = al; }
            if (x + 2 == ar) { remove_interval(r); b = br; }
            add_interval(a, b);
        }
    }

    void add_fib(int x) {
        auto p = prev(intervals.lower_bound({x + 1, x + 1}));
        
        // C++17 구조적 바인딩 대신 명시적으로 first, second 할당
        int a = p->first;
        int b = p->second;

        if (x < a || b < x) {
            add_fib_out(x);
        } else if ((a ^ x) & 1) { // 홀수 거리 (충돌 병합)
            remove_interval(p);
            add_interval(a, x - 1);
            add_fib_out(b + 1);
        } else { // 짝수 거리 (분할)
            remove_interval(p);
            add_interval(a + 1, x - 1);
            for (int y : {a - 2, b + 1}) {
                if (y > -1) add_fib_out(max(1, y));
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    ZeckendorfManager zm(n);

    // 1단계 : 쿼리 처리 및 이벤트 기록 (BBST 활용)
    for (zm.current_step = 0; zm.current_step < n; ++zm.current_step) {
        int x;
        cin >> x;
        zm.add_fib(x);
    }

    // 2단계 : 오프라인 쿼리를 위한 좌표 압축 및 초기화
    vector<pii> all_intervals;
    all_intervals.emplace_back(0, 0); // 더미 노드

    for (int i = 0; i < n; ++i) {
        all_intervals.insert(all_intervals.end(), zm.event_log[i].begin(), zm.event_log[i].end());
    }

    sort(all_intervals.begin(), all_intervals.end());
    all_intervals.erase(unique(all_intervals.begin(), all_intervals.end()), all_intervals.end());

    SegmentTree seg_tree(all_intervals.size());
    for (size_t i = 0; i < all_intervals.size(); ++i) {
        seg_tree.init_node(i, all_intervals[i]);
    }
    
    seg_tree.toggle(0); // 더미 노드 활성화

    // 3단계 : 기록된 이벤트를 세그먼트 트리에 반영하며 정답 출력
    for (int i = 0; i < n; ++i) {
        for (const auto& v : zm.event_log[i]) {
            int index = lower_bound(all_intervals.begin(), all_intervals.end(), v) - all_intervals.begin();
            seg_tree.toggle(index);
        }
        cout << seg_tree.query() << "\n";
    }

    return 0;
}