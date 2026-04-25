// 13539(트리와 쿼리 11) 문제 : https://www.acmicpc.net/problem/13539
// 알고리즘 태그 목록
/*
트리
링크/컷 트리
*/
#include <bits/stdc++.h>

using namespace std;

struct LCT {
    struct Node {
        int ch[2];
        int p;

        Node() {
            ch[0] = ch[1] = p = 0;
        }
    };

    vector<Node> tree;

    LCT(int n) : tree(n + 1) {}

    bool is_root(int x) {
        int parent = tree[x].p;
        if (!parent) return true;
        return tree[parent].ch[0] != x && tree[parent].ch[1] != x;
    }

    void rotate(int x) {
        int y = tree[x].p;
        int z = tree[y].p;
        int k = (tree[y].ch[1] == x);

        if (!is_root(y)) {
            tree[z].ch[tree[z].ch[1] == y] = x;
        }
        tree[x].p = z;

        tree[y].ch[k] = tree[x].ch[k ^ 1];
        if (tree[x].ch[k ^ 1]) {
            tree[tree[x].ch[k ^ 1]].p = y;
        }

        tree[x].ch[k ^ 1] = y;
        tree[y].p = x;
    }

    void splay(int x) {
        while (!is_root(x)) {
            int y = tree[x].p;
            int z = tree[y].p;
            if (!is_root(y)) {
                (tree[y].ch[1] == x) == (tree[z].ch[1] == y) ? rotate(y) : rotate(x);
            }
            rotate(x);
        }
    }

    int access(int x) {
        int last = 0;
        for (int current = x; current; current = tree[current].p) {
            splay(current);
            tree[current].ch[1] = last;
            last = current;
        }
        splay(x);
        return last;
    }

    void link(int u, int v) {
        access(u);
        tree[u].p = v;
    }

    void cut(int v) {
        access(v);
        if (tree[v].ch[0]) {
            tree[tree[v].ch[0]].p = 0;
            tree[v].ch[0] = 0;
        }
    }

    int get_lca(int u, int v) {
        access(u);
        return access(v);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    LCT lct(n);

    while (m--) {
        int type;
        cin >> type;

        if (type == 1) {
            int u, v;
            cin >> u >> v;
            lct.link(u, v);
        } else if (type == 2) {
            int v;
            cin >> v;
            lct.cut(v);
        } else if (type == 3) {
            int u, v;
            cin >> u >> v;
            cout << lct.get_lca(u, v) << "\n";
        }
    }

    return 0;
}