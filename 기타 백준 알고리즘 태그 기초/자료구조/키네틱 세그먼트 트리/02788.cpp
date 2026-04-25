// 2788(스타트업) 문제 : https://www.acmicpc.net/problem/2788
// 알고리즘 태그 목록
/*
자료 구조
세그먼트 트리
느리게 갱신되는 세그먼트 트리
볼록 껍질을 이용한 최적화
키네틱 세그먼트 트리
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 2e18;

struct Line {
    ll a, b;

    ll eval(ll t) const {
        if (b == INF) return INF;
        return a * t + b;
    }

    bool operator!=(const Line& other) const {
        return a != other.a || b != other.b;
    }
};

struct KineticSegmentTree {
    int n;
    ll current_time;
    vector<Line> tree;
    vector<ll> melt;

    KineticSegmentTree(int _n) : n(_n), current_time(0) {
        tree.assign(4 * n + 1, {0, INF});
        melt.assign(4 * n + 1, INF);
    }

    ll get_next_event(const Line& l1, const Line& l2) {
        if (l1.a > l2.a) {
            ll d_val = l2.eval(current_time) - l1.eval(current_time);
            ll d_slope = l1.a - l2.a;
            ll next_t = current_time + (d_val / d_slope) + 1;
            return next_t > current_time ? next_t : INF;
        }
        return INF;
    }

    bool compare(const Line& l1, const Line& l2) {
        ll val1 = l1.eval(current_time);
        ll val2 = l2.eval(current_time);
        if (val1 != val2) return val1 < val2;
        return l1.a < l2.a;
    }

    void update_structure(int node, int start, int end) {
        if (start == end || melt[node] > current_time) return;

        int mid = (start + end) / 2;
        update_structure(node * 2 + 1, start, mid);
        update_structure(node * 2 + 2, mid + 1, end);

        Line l1 = tree[node * 2 + 1];
        Line l2 = tree[node * 2 + 2];

        if (!compare(l1, l2)) swap(l1, l2);
        
        tree[node] = l1;
        melt[node] = min(melt[node * 2 + 1], melt[node * 2 + 2]);
        if (l1 != l2) {
            melt[node] = min(melt[node], get_next_event(l1, l2));
        }
    }

    void update_line(int node, int start, int end, int idx, ll a, ll b) {
        if (idx < start || idx > end) return;
        if (start == end) {
            tree[node] = {a, b};
            return;
        }

        int mid = (start + end) / 2;
        update_line(node * 2 + 1, start, mid, idx, a, b);
        update_line(node * 2 + 2, mid + 1, end, idx, a, b);
        
        melt[node] = 0;
        update_structure(node, start, end);
    }

    ll get_min(int node, int start, int end, int left, int right) {
        if (end < left || start > right) return INF;
        
        update_structure(node, start, end);
        
        if (left <= start && end <= right) return tree[node].eval(current_time);
        
        int mid = (start + end) / 2;
        return min(get_min(node * 2 + 1, start, mid, left, right),
                   get_min(node * 2 + 2, mid + 1, end, left, right));
    }

    void heaten(ll new_t) {
        current_time = new_t;
        update_structure(0, 0, n - 1);
    }

    void set_max_line(int idx, ll slope, ll intercept) {
        update_line(0, 0, n - 1, idx, -slope, -intercept + current_time * slope);
    }

    ll query_max(int l, int r) {
        ll res = get_min(0, 0, n - 1, l, r);
        return (res >= INF / 2) ? -1 : -res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    KineticSegmentTree kst(1000001);

    while (m--) {
        int type;
        cin >> type;
        if (type == 1) {
            ll t, k, z, s;
            cin >> t >> k >> z >> s;
            kst.heaten(t);
            kst.update_line(0, 0, 1000000, k, -z, -(s - t * z));
        } else {
            ll t, a, b;
            cin >> t >> a >> b;
            if (a > b) swap(a, b);
            kst.heaten(t);
            ll result = kst.get_min(0, 0, 1000000, a, b);
            if (result >= INF / 2) cout << "nema\n";
            else cout << -result << "\n";
        }
    }

    return 0;
}