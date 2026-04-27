// 27440(1로 만들기 3) 문제 : https://www.acmicpc.net/problem/27440
// 알고리즘 태그 목록
/*
자료 구조
그래프 이론
그래프 탐색
집합과 맵
너비 우선 탐색
해시를 사용한 집합과 맵
트리를 사용한 집합과 맵
*/
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// N이 10^18까지이므로 long long 필수
using ll = long long;

ll bfs(ll node) {
    // S1: 전체 방문한 원소들을 저장 (해시셋 대신 트리셋인 std::set 사용)
    // std::set은 내부적으로 Red-Black Tree를 사용하여 탐색/삽입에 O(log N)이 소요됩니다.
    set<ll> s1;

    // 현재 depth의 원소들을 담는 큐 (파이썬의 queue:list 역할)
    vector<ll> current_level;
    current_level.push_back(node);

    ll depth = -1;

    while (!current_level.empty()) {
        depth++;

        // 현재 레벨의 원소들을 방문 셋(S1)에 기록
        for (ll val : current_level) {
            s1.insert(val);
        }

        // S2: 다음 레벨에 방문할 원소들을 저장 (중복 제거를 위해 트리셋 사용)
        set<ll> s2;

        for (ll i : current_level) {
            if (i == 1) return depth;

            // 연산 1: i - 1
            if (i - 1 >= 1 && s1.find(i - 1) == s1.end()) {
                s2.insert(i - 1);
            }
            // 연산 2: i / 2
            if (i % 2 == 0 && s1.find(i / 2) == s1.end()) {
                s2.insert(i / 2);
            }
            // 연산 3: i / 3
            if (i % 3 == 0 && s1.find(i / 3) == s1.end()) {
                s2.insert(i / 3);
            }
        }

        // 다음 레벨 탐색을 위해 큐 업데이트
        current_level.clear();
        for (ll next_val : s2) {
            current_level.push_back(next_val);
        }
    }
    return depth;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    cout << bfs(n) << "\n";

    return 0;
}