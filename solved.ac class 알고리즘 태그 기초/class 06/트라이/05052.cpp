// 5052(전화번호 목록) 문제 : https://www.acmicpc.net/problem/5052
// 알고리즘 태그 목록
/*
자료 구조
문자열
정렬
트리
집합과 맵
트라이
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 트라이 노드 구조체
struct Node {
    Node* child[10];
    bool is_end;

    Node() {
        for (int i = 0; i < 10; i++) child[i] = nullptr;
        is_end = false;
    }

    // 메모리 해제를 위한 소멸자
    ~Node() {
        for (int i = 0; i < 10; i++) {
            if (child[i]) delete child[i];
        }
    }

    // 문자열 삽입 및 일관성 체크
    bool insert(const char* str) {
        // 문자열이 끝났을 때
        if (*str == '\0') {
            is_end = true;
            // 만약 현재 노드에 자식이 있다면, 이 번호는 다른 번호의 접두어임
            for (int i = 0; i < 10; i++) {
                if (child[i]) return false;
            }
            return true;
        }

        // 삽입 도중 이미 끝난 번호를 만난다면, 그 번호가 현재 번호의 접두어임
        if (is_end) return false;

        int next = *str - '0';
        if (!child[next]) child[next] = new Node();
        
        return child[next]->insert(str + 1);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<string> phone_numbers(n);
    for (int i = 0; i < n; i++) {
        cin >> phone_numbers[i];
    }

    // 정렬을 하면 접두어 관계인 번호들이 인접하게 되어 처리가 더 확실해집니다.
    // 하지만 트라이만으로도 해결 가능하므로 여기서는 트라이 로직에 집중합니다.
    sort(phone_numbers.begin(), phone_numbers.end());

    Node* root = new Node();
    bool consistent = true;

    for (const string& s : phone_numbers) {
        if (!root->insert(s.c_str())) {
            consistent = false;
            break;
        }
    }

    if (consistent) cout << "YES" << "\n";
    else cout << "NO" << "\n";

    delete root; // 전체 트리 메모리 해제
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}