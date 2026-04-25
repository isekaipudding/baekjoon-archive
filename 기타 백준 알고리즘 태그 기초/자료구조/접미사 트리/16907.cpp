// 16907(서로 다른 부분 문자열 쿼리 2) 문제 : https://www.acmicpc.net/problem/16907
// 알고리즘 태그 목록
/*
자료 구조
문자열
트리
세그먼트 트리
오프라인 쿼리
트라이
접미사 배열과 lcp 배열
접미사 트리
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SAM {
    struct State {
        int len, link;
        int nxt[26];

        State() {
            len = 0;
            link = -1;
            memset(nxt, 0, sizeof(nxt));
        }
    };

    vector<State> states;
    int last;
    ll total_distinct;

    SAM() {
        states.emplace_back();
        last = 0;
        total_distinct = 0;
    }

    int create_state(int len, int link = -1) {
        State st;
        st.len = len;
        st.link = link;
        states.push_back(st);
        return states.size() - 1;
    }

    void update_link(int u, int new_link) {
        if (states[u].link != -1) {
            total_distinct -= (states[u].len - states[states[u].link].len);
        }
        
        states[u].link = new_link;
        
        if (states[u].link != -1) {
            total_distinct += (states[u].len - states[states[u].link].len);
        }
    }

    void extend(int c) {
        int cur = create_state(states[last].len + 1);
        int p = last;

        while (p != -1 && !states[p].nxt[c]) {
            states[p].nxt[c] = cur;
            p = states[p].link;
        }

        if (p == -1) {
            update_link(cur, 0);
        } else {
            int q = states[p].nxt[c];
            if (states[p].len + 1 == states[q].len) {
                update_link(cur, q);
            } else {
                
                int clone = create_state(states[p].len + 1, states[q].link);
                memcpy(states[clone].nxt, states[q].nxt, sizeof(states[q].nxt));
                
                while (p != -1 && states[p].nxt[c] == q) {
                    states[p].nxt[c] = clone;
                    p = states[p].link;
                }
                update_link(q, clone);
                update_link(cur, clone);
            }
        }
        last = cur;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    SAM sa;

    for (char c : s) {
        if (c == '?') {
            cout << sa.total_distinct << "\n";
        } else {
            sa.extend(c - 'a');
        }
    }

    return 0;
}