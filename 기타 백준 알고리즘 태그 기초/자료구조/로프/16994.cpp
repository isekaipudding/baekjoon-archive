// 16994(로프와 쿼리) 문제 : https://www.acmicpc.net/problem/16994
// 알고리즘 태그 목록
/*
자료 구조
문자열
트리
스플레이 트리
로프
*/
#include <bits/stdc++.h>

using namespace std;

// 트립(Treap)을 이용한 로프(Rope) 구현
struct Treap {
    struct Node {
        int val;      // 원본 문자열의 인덱스
        int priority; // 무작위 우선순위
        int size;     // 서브트리의 크기
        int ch[2];    // 자식 노드 인덱스

        Node() : val(0), priority(0), size(0) {
            ch[0] = ch[1] = 0;
        }
        Node(int v) : val(v), size(1) {
            priority = rand();
            ch[0] = ch[1] = 0;
        }
    };

    vector<Node> tree;
    int root;
    int node_count;

    Treap(int n) {
        srand(time(NULL));
        // 메모리 재할당 방지를 위해 미리 공간 예약
        tree.resize(n + 1);
        node_count = 0;
        root = build(0, n - 1);
    }

    void push_up(int u) {
        if (!u) return;
        tree[u].size = 1 + tree[tree[u].ch[0]].size + tree[tree[u].ch[1]].size;
    }

    // O(N) 빌드 시 힙 성질 유지를 위한 함수
    void heapify(int u) {
        if (!u) return;
        int max_node = u;
        if (tree[u].ch[0] && tree[tree[u].ch[0]].priority > tree[max_node].priority)
            max_node = tree[u].ch[0];
        if (tree[u].ch[1] && tree[tree[u].ch[1]].priority > tree[max_node].priority)
            max_node = tree[u].ch[1];
        
        if (max_node != u) {
            swap(tree[u].priority, tree[max_node].priority);
            heapify(max_node);
        }
    }

    int build(int s, int e) {
        if (s > e) return 0;
        int mid = (s + e) / 2;
        
        int u = ++node_count;
        tree[u] = Node(mid);
        
        // 재귀 호출 시 인덱스를 사용하여 메모리 안전성 확보
        int left_child = build(s, mid - 1);
        tree[u].ch[0] = left_child;
        
        int right_child = build(mid + 1, e);
        tree[u].ch[1] = right_child;
        
        heapify(u);
        push_up(u);
        return u;
    }

    // 트리를 크기 k를 기준으로 분할
    void split(int u, int k, int& l, int& r) {
        if (!u) {
            l = r = 0;
            return;
        }
        int left_size = tree[tree[u].ch[0]].size;
        if (left_size < k) {
            l = u;
            split(tree[u].ch[1], k - left_size - 1, tree[u].ch[1], r);
        } else {
            r = u;
            split(tree[u].ch[0], k, l, tree[u].ch[0]);
        }
        push_up(u);
    }

    // 두 트리를 하나로 병합
    int merge(int l, int r) {
        if (!l || !r) return l ? l : r;
        if (tree[l].priority > tree[r].priority) {
            tree[l].ch[1] = merge(tree[l].ch[1], r);
            push_up(l);
            return l;
        } else {
            tree[r].ch[0] = merge(l, tree[r].ch[0]);
            push_up(r);
            return r;
        }
    }

    void move_to_front(int i, int j) {
        int t1, t2, t3;
        split(root, i, t1, t2);
        split(t2, j - i + 1, t2, t3);
        root = merge(merge(t2, t1), t3);
    }

    void move_to_back(int i, int j) {
        int t1, t2, t3;
        split(root, i, t1, t2);
        split(t2, j - i + 1, t2, t3);
        root = merge(merge(t1, t3), t2);
    }

    int get_char_index(int i) {
        int curr = root;
        while (curr) {
            int left_size = tree[tree[curr].ch[0]].size;
            if (i < left_size) {
                curr = tree[curr].ch[0];
            } else if (i > left_size) {
                i -= (left_size + 1);
                curr = tree[curr].ch[1];
            } else {
                return tree[curr].val;
            }
        }
        return -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    Treap tr(s.size());

    int q;
    cin >> q;
    while (q--) {
        int type, i, j;
        cin >> type;
        if (type == 1) {
            cin >> i >> j;
            tr.move_to_front(i, j);
        } else if (type == 2) {
            cin >> i >> j;
            tr.move_to_back(i, j);
        } else {
            cin >> i;
            cout << s[tr.get_char_index(i)] << "\n";
        }
    }

    return 0;
}