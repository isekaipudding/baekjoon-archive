// 17936(트리와 쿼리 13) 문제 : https://www.acmicpc.net/problem/17936
// 알고리즘 태그 목록
/*
자료 구조
트리
링크/컷 트리
탑 트리
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 2e18; // i64::MAX 대용

struct Data {
    ll sum, min_val, max_val, size;

    Data() : sum(0), min_val(INF), max_val(-INF), size(0) {}
    Data(ll val) : sum(val), min_val(val), max_val(val), size(1) {}

    static Data merge(const Data& a, const Data& b) {
        Data res;
        res.sum = a.sum + b.sum;
        res.min_val = min(a.min_val, b.min_val);
        res.max_val = max(a.max_val, b.max_val);
        res.size = a.size + b.size;
        return res;
    }
};

struct Lazy {
    ll a, b; // ax + b 형태의 선형 변환

    Lazy() : a(1), b(0) {}
    Lazy(ll _a, ll _b) : a(_a), b(_b) {}

    bool is_lazy() const { return a != 1 || b != 0; }

    static Lazy merge(const Lazy& old_l, const Lazy& new_l) {
        // new_l(old_l(x)) = new_l.a * (old_l.a * x + old_l.b) + new_l.b
        return Lazy(old_l.a * new_l.a, old_l.b * new_l.a + new_l.b);
    }

    static ll apply(ll val, const Lazy& l) {
        return val * l.a + l.b;
    }

    static Data apply_to_data(const Data& d, const Lazy& l) {
        if (d.size == 0) return d;
        Data res;
        res.sum = d.sum * l.a + l.b * d.size;
        res.min_val = d.min_val * l.a + l.b;
        res.max_val = d.max_val * l.a + l.b;
        res.size = d.size;
        // a가 0일 경우 (대입 연산), min/max가 역전될 수 있으므로 정렬 필요
        if (res.min_val > res.max_val) swap(res.min_val, res.max_val);
        return res;
    }
};

struct TopTree {
    struct Node {
        int p, ch[4]; // 0,1: Preferred, 2,3: Virtual
        ll val;
        Data path, subtree, all;
        Lazy lazy_path, lazy_subtree;
        bool flip, is_fake;

        Node() : p(0), val(0), flip(false), is_fake(true) {
            memset(ch, 0, sizeof(ch));
        }
        Node(ll v) : p(0), val(v), flip(false), is_fake(false) {
            memset(ch, 0, sizeof(ch));
            path = all = Data(v);
        }
    };

    vector<Node> tree;
    vector<int> fake_nodes;

    TopTree(int n) {
        tree.resize(2 * n + 1);
        for (int i = n + 1; i <= 2 * n; ++i) {
            fake_nodes.push_back(i);
        }
    }

    void push_flip(int u) {
        if (!u) return;
        swap(tree[u].ch[0], tree[u].ch[1]);
        tree[u].flip ^= true;
    }

    void push_path(int u, const Lazy& l) {
        if (!u || tree[u].is_fake) return;
        tree[u].val = Lazy::apply(tree[u].val, l);
        tree[u].path = Lazy::apply_to_data(tree[u].path, l);
        tree[u].all = Data::merge(tree[u].path, tree[u].subtree);
        tree[u].lazy_path = Lazy::merge(tree[u].lazy_path, l);
    }

    void push_subtree(int u, bool is_virtual, const Lazy& l) {
        if (!u) return;
        tree[u].subtree = Lazy::apply_to_data(tree[u].subtree, l);
        tree[u].lazy_subtree = Lazy::merge(tree[u].lazy_subtree, l);
        if (!tree[u].is_fake && is_virtual) {
            push_path(u, l);
        } else {
            tree[u].all = Data::merge(tree[u].path, tree[u].subtree);
        }
    }

    void push(int u) {
        if (!u) return;
        if (tree[u].flip) {
            push_flip(tree[u].ch[0]);
            push_flip(tree[u].ch[1]);
            tree[u].flip = false;
        }
        if (tree[u].lazy_path.is_lazy()) {
            push_path(tree[u].ch[0], tree[u].lazy_path);
            push_path(tree[u].ch[1], tree[u].lazy_path);
            tree[u].lazy_path = Lazy();
        }
        if (tree[u].lazy_subtree.is_lazy()) {
            push_subtree(tree[u].ch[0], false, tree[u].lazy_subtree);
            push_subtree(tree[u].ch[1], false, tree[u].lazy_subtree);
            push_subtree(tree[u].ch[2], true, tree[u].lazy_subtree);
            push_subtree(tree[u].ch[3], true, tree[u].lazy_subtree);
            tree[u].lazy_subtree = Lazy();
        }
    }

    void pull(int u) {
        if (!u) return;
        if (!tree[u].is_fake) {
            Data path_pref = Data::merge(tree[tree[u].ch[0]].path, tree[tree[u].ch[1]].path);
            tree[u].path = Data::merge(path_pref, Data(tree[u].val));
        }
        Data sub_pref = Data::merge(tree[tree[u].ch[0]].subtree, tree[tree[u].ch[1]].subtree);
        Data all_virt = Data::merge(tree[tree[u].ch[2]].all, tree[tree[u].ch[3]].all);
        tree[u].subtree = Data::merge(sub_pref, all_virt);
        tree[u].all = Data::merge(tree[u].path, tree[u].subtree);
    }

    void attach(int u, int dir, int v) {
        tree[u].ch[dir] = v;
        tree[v].p = u;
        pull(u);
    }

    int direction(int u, int pos) {
        int v = tree[u].p;
        if (tree[v].ch[pos] == u) return pos;
        if (tree[v].ch[pos + 1] == u) return pos + 1;
        return -1;
    }

    void rotate(int u, int pos) {
        int v = tree[u].p, w = tree[v].p;
        int du = direction(u, pos), dv = direction(v, pos);
        if (dv == -1 && pos == 0) dv = direction(v, 2);

        if (du != -1) {
            attach(v, du, tree[u].ch[du ^ 1]);
            attach(u, du ^ 1, v);
        }
        if (dv != -1) attach(w, dv, u);
        else tree[u].p = w;
    }

    void splay(int u, int pos) {
        push(u);
        while (direction(u, pos) != -1 && (pos == 0 || tree[tree[u].p].is_fake)) {
            int v = tree[u].p, w = tree[v].p;
            push(w); push(v); push(u);
            int du = direction(u, pos), dv = direction(v, pos);
            if (dv != -1 && (pos == 0 || tree[w].is_fake)) {
                if (du == dv) rotate(v, pos);
                else rotate(u, pos);
            }
            rotate(u, pos);
        }
    }

    void add_virtual(int u, int v) {
        if (!v) return;
        for (int i = 2; i < 4; ++i) {
            if (!tree[u].ch[i]) {
                attach(u, i, v);
                return;
            }
        }
        int w = fake_nodes.back(); fake_nodes.pop_back();
        tree[w] = Node(); tree[w].is_fake = true;
        attach(w, 2, tree[u].ch[2]);
        attach(w, 3, v);
        attach(u, 2, w);
    }

    void push_recursive(int u) {
        if (tree[u].is_fake) push_recursive(tree[u].p);
        push(u);
    }

    void remove_virtual(int u) {
        int v = tree[u].p;
        push_recursive(v);
        int du = direction(u, 2), dv = direction(v, 2);
        if (tree[v].is_fake) {
            int w = tree[v].p;
            if (du != -1 && dv != -1) attach(w, dv, tree[v].ch[du ^ 1]);
            if (tree[w].is_fake) splay(w, 2);
            fake_nodes.push_back(v);
        } else if (du != -1) attach(v, du, 0);
        tree[u].p = 0;
    }

    int access(int u) {
        int v = u;
        splay(u, 0);
        add_virtual(u, tree[u].ch[1]);
        attach(u, 1, 0);
        while (tree[u].p) {
            int p = tree[u].p;
            if (tree[p].is_fake) { splay(p, 2); p = tree[p].p; }
            v = p;
            splay(v, 0);
            remove_virtual(u);
            add_virtual(v, tree[v].ch[1]);
            attach(v, 1, u);
            splay(u, 0);
        }
        return v;
    }

    void make_root(int u) {
        access(u);
        push_flip(u);
    }

    void link(int u, int v) {
        make_root(u);
        access(v);
        add_virtual(v, u);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<pair<int, int>> edges(n - 1);
    for (int i = 0; i < n - 1; ++i) cin >> edges[i].first >> edges[i].second;

    TopTree tt(n);
    for (int i = 1; i <= n; ++i) {
        ll val; cin >> val;
        tt.tree[i] = TopTree::Node(val);
    }

    int r; cin >> r;
    for (auto& e : edges) tt.link(e.first, e.second);

    while (m--) {
        int op, x, y; ll z;
        cin >> op;
        if (op == 0) { // 서브트리 대입
            cin >> x >> z;
            tt.make_root(r); tt.access(x);
            Lazy l(0, z);
            tt.tree[x].val = Lazy::apply(tt.tree[x].val, l);
            for (int i = 2; i < 4; ++i) tt.push_subtree(tt.tree[x].ch[i], true, l);
        } else if (op == 1) { // 루트 변경
            cin >> r;
        } else if (op == 2) { // 경로 대입
            cin >> x >> y >> z;
            tt.make_root(x); tt.access(y);
            tt.push_path(y, Lazy(0, z));
        } else if (op == 3) { // 서브트리 최소값
            cin >> x;
            tt.make_root(r); tt.access(x);
            Data res(tt.tree[x].val);
            for (int i = 2; i < 4; ++i) res = Data::merge(res, tt.tree[tt.tree[x].ch[i]].all);
            cout << res.min_val << "\n";
        } else if (op == 4) { // 서브트리 최대값
            cin >> x;
            tt.make_root(r); tt.access(x);
            Data res(tt.tree[x].val);
            for (int i = 2; i < 4; ++i) res = Data::merge(res, tt.tree[tt.tree[x].ch[i]].all);
            cout << res.max_val << "\n";
        } else if (op == 5) { // 서브트리 더하기
            cin >> x >> z;
            tt.make_root(r); tt.access(x);
            Lazy l(1, z);
            tt.tree[x].val = Lazy::apply(tt.tree[x].val, l);
            for (int i = 2; i < 4; ++i) tt.push_subtree(tt.tree[x].ch[i], true, l);
        } else if (op == 6) { // 경로 더하기
            cin >> x >> y >> z;
            tt.make_root(x); tt.access(y);
            tt.push_path(y, Lazy(1, z));
        } else if (op == 7) { // 경로 최소값
            cin >> x >> y;
            tt.make_root(x); tt.access(y);
            cout << tt.tree[y].path.min_val << "\n";
        } else if (op == 8) { // 경로 최대값
            cin >> x >> y;
            tt.make_root(x); tt.access(y);
            cout << tt.tree[y].path.max_val << "\n";
        } else if (op == 9) { // 부모 변경 (Link/Cut)
            cin >> x >> y;
            tt.make_root(r); tt.access(y);
            if (tt.access(x) != x) {
                int child = tt.tree[x].ch[0];
                tt.tree[child].p = 0;
                tt.tree[x].ch[0] = 0;
                tt.pull(x); tt.access(y); tt.add_virtual(y, x);
            }
        } else if (op == 10) { // 경로 합
            cin >> x >> y;
            tt.make_root(x); tt.access(y);
            cout << tt.tree[y].path.sum << "\n";
        } else if (op == 11) { // 서브트리 합
            cin >> x;
            tt.make_root(r); tt.access(x);
            Data res(tt.tree[x].val);
            for (int i = 2; i < 4; ++i) res = Data::merge(res, tt.tree[tt.tree[x].ch[i]].all);
            cout << res.sum << "\n";
        }
    }
    return 0;
}