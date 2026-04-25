// 10066(팰린드롬) 문제 : https://www.acmicpc.net/problem/10066
// 알고리즘 태그 목록
/*
자료 구조
문자열
트리
접미사 배열과 lcp 배열
매내처
회문 트리
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct PalindromicTree {
    struct Node {
        int ch[26];
        int link;
        int len;
        ll count;

        Node(int l = 0) : len(l), link(0), count(0) {
            memset(ch, 0, sizeof(ch));
        }
    };

    string s;
    vector<Node> tree;
    int last;

    PalindromicTree(const string& str) : s(str) {
        tree.emplace_back(-1);
        tree[0].link = 0;

        tree.emplace_back(0);
        tree[1].link = 0;

        last = 0;
    }

    int get_link(int x, int i) {
        while (i - 1 - tree[x].len < 0 || s[i - 1 - tree[x].len] != s[i]) {
            x = tree[x].link;
        }
        return x;
    }

    void extend(int i) {
        int char_index = s[i] - 'a';
        int p = get_link(last, i);

        if (!tree[p].ch[char_index]) {
            int new_node = tree.size();
            int new_len = tree[p].len + 2;
            tree.emplace_back(new_len);

            if (new_len == 1) {
                tree[new_node].link = 1;
            } else {
                tree[new_node].link = tree[get_link(tree[p].link, i)].ch[char_index];
            }
            tree[p].ch[char_index] = new_node;
        }

        last = tree[p].ch[char_index];
        tree[last].count++;
    }

    void build_frequencies() {
        for (int i = tree.size() - 1; i > 1; --i) {
            tree[tree[i].link].count += tree[i].count;
        }
    }

    ll solve() {
        ll max_value = 0;
        for (int i = 2; i < tree.size(); ++i) {
            max_value = max(max_value, (ll)tree[i].len * tree[i].count);
        }
        return max_value;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    PalindromicTree pt(s);
    for (int i = 0; i < s.length(); ++i) {
        pt.extend(i);
    }

    pt.build_frequencies();
    cout << pt.solve() << "\n";

    return 0;
}