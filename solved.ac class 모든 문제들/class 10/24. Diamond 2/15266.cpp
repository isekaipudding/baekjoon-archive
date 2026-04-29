// 15266(Intrinsic Interval) 문제 : https://www.acmicpc.net/problem/15266
// 알고리즘 태그 목록
/*
자료 구조
세그먼트 트리
오프라인 쿼리
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

const int MAXN = 100005;
const int INF = 1e9;

struct Node {
    int min_val;
    int min_query_val;
    int lazy;
    vector<int> queries;
} tree[MAXN * 4];

int n;
int pi[MAXN];
int query_x[MAXN];
vector<int> queries_at[MAXN];
int result_L[MAXN], result_R[MAXN];

void push_up(int v, int l, int r) {
    if (l != r) {
        tree[v].min_val = min(tree[2 * v].min_val, tree[2 * v + 1].min_val);
    }
    tree[v].min_query_val = INF;
    if (!tree[v].queries.empty()) {
        tree[v].min_query_val = tree[v].min_val;
    }
    if (l != r) {
        tree[v].min_query_val = min({tree[v].min_query_val, tree[2 * v].min_query_val, tree[2 * v + 1].min_query_val});
    }
}

void apply(int v, int tag) {
    tree[v].min_val += tag;
    if (tree[v].min_query_val != INF) {
        tree[v].min_query_val += tag;
    }
    tree[v].lazy += tag;
}

void push_down(int v, int l, int r) {
    if (tree[v].lazy != 0 && l != r) {
        apply(2 * v, tree[v].lazy);
        apply(2 * v + 1, tree[v].lazy);
        tree[v].lazy = 0;
    }
}

void build(int v, int l, int r) {
    tree[v].min_val = l;
    tree[v].min_query_val = INF;
    tree[v].lazy = 0;
    if (l == r) return;
    int mid = (l + r) / 2;
    build(2 * v, l, mid);
    build(2 * v + 1, mid + 1, r);
    push_up(v, l, r);
}

void update_range(int v, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        apply(v, val);
        return;
    }
    push_down(v, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) update_range(2 * v, l, mid, ql, qr, val);
    if (qr > mid) update_range(2 * v + 1, mid + 1, r, ql, qr, val);
    push_up(v, l, r);
}

int query_min(int v, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[v].min_val;
    push_down(v, l, r);
    int mid = (l + r) / 2;
    int result = INF;
    if (ql <= mid) result = min(result, query_min(2 * v, l, mid, ql, qr));
    if (qr > mid) result = min(result, query_min(2 * v + 1, mid + 1, r, ql, qr));
    return result;
}

void add_query(int v, int l, int r, int ql, int qr, int q_index) {
    if (ql <= l && r <= qr) {
        tree[v].queries.push_back(q_index);
        tree[v].min_query_val = min(tree[v].min_query_val, tree[v].min_val);
        return;
    }
    push_down(v, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) add_query(2 * v, l, mid, ql, qr, q_index);
    if (qr > mid) add_query(2 * v + 1, mid + 1, r, ql, qr, q_index);
    push_up(v, l, r);
}

int find_rightmost_zero(int v, int l, int r, int ql, int qr, int R_val) {
    if (tree[v].min_val > R_val) return -1;
    if (ql <= l && r <= qr) {
        if (l == r) return l;
        push_down(v, l, r);
        int mid = (l + r) / 2;
        if (tree[2 * v + 1].min_val == R_val) {
            int result = find_rightmost_zero(2 * v + 1, mid + 1, r, ql, qr, R_val);
            if (result != -1) return result;
        }
        return find_rightmost_zero(2 * v, l, mid, ql, qr, R_val);
    }
    push_down(v, l, r);
    int mid = (l + r) / 2;
    int result = -1;
    if (qr > mid) result = find_rightmost_zero(2 * v + 1, mid + 1, r, ql, qr, R_val);
    if (result == -1 && ql <= mid) result = find_rightmost_zero(2 * v, l, mid, ql, qr, R_val);
    return result;
}

void result_queries(int v, int l, int r, int R_val) {
    if (tree[v].min_query_val > R_val) return;

    if (!tree[v].queries.empty()) {
        vector<int> active;
        bool changed = false;
        for (int q_index : tree[v].queries) {
            if (result_R[q_index] == 0) {
                if (tree[v].min_val == R_val) {
                    result_R[q_index] = R_val;
                    result_L[q_index] = find_rightmost_zero(1, 1, n, 1, query_x[q_index], R_val);
                    changed = true;
                } else {
                    active.push_back(q_index);
                }
            } else {
                changed = true;
            }
        }
        if (changed) {
            tree[v].queries = active;
        }
    }

    if (l == r) {
        push_up(v, l, r);
        return;
    }

    push_down(v, l, r);
    int mid = (l + r) / 2;
    result_queries(2 * v, l, mid, R_val);
    result_queries(2 * v + 1, mid + 1, r, R_val);
    push_up(v, l, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    n = readInt();
    for (int i = 1; i <= n; i++) {
        pi[i] = readInt();
    }

    int m = readInt();
    for (int i = 1; i <= m; i++) {
        query_x[i] = readInt();
        int y = readInt();
        queries_at[y].push_back(i);
    }

    build(1, 1, n);

    vector<int> stack_max, stack_min;

    for (int R = 1; R <= n; R++) {
        while (!stack_max.empty() && pi[stack_max.back()] < pi[R]) {
            int index = stack_max.back();
            stack_max.pop_back();
            int left_bound = stack_max.empty() ? 1 : stack_max.back() + 1;
            update_range(1, 1, n, left_bound, index, pi[R] - pi[index]);
        }
        stack_max.push_back(R);

        while (!stack_min.empty() && pi[stack_min.back()] > pi[R]) {
            int index = stack_min.back();
            stack_min.pop_back();
            int left_bound = stack_min.empty() ? 1 : stack_min.back() + 1;
            update_range(1, 1, n, left_bound, index, pi[index] - pi[R]);
        }
        stack_min.push_back(R);

        for (int q_index : queries_at[R]) {
            int min_v = query_min(1, 1, n, 1, query_x[q_index]);
            if (min_v == R) {
                result_R[q_index] = R;
                result_L[q_index] = find_rightmost_zero(1, 1, n, 1, query_x[q_index], R);
            } else {
                add_query(1, 1, n, 1, query_x[q_index], q_index);
            }
        }

        result_queries(1, 1, n, R);
    }

    for (int i = 1; i <= m; i++) {
        cout << result_L[i] << " " << result_R[i] << "\n";
    }

    return 0;
}