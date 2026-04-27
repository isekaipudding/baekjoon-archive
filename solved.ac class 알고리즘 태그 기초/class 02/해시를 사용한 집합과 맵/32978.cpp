// 32978(아 맞다 마늘) 문제 : https://www.acmicpc.net/problem/32978
// 알고리즘 태그 목록
/*
구현
자료 구조
문자열
브루트포스 알고리즘
집합과 맵
해시를 사용한 집합과 맵
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n; // 전체 재료의 개수 입력

    // 1. 원래 필요했던 재료 목록을 순서대로 저장
    // 나중에 정답을 찾기 위해 vector에 보관합니다.
    vector<string> required(n);
    for (int i = 0; i < n; i++) {
        cin >> required[i];
    }

    // 2. 실제로 사용한 재료 목록을 unordered_set에 저장
    // 특정 재료가 사용되었는지 빠르게(O(1)) 확인하기 위함입니다.
    unordered_set<string> used;
    for (int i = 0; i < n - 1; i++) {
        string ingredient;
        cin >> ingredient;
        used.insert(ingredient);
    }

    // 3. 전체 목록을 순회하며 used 세트에 없는 재료를 찾음
    for (int i = 0; i < n; i++) {
        // used.count() 혹은 used.find()를 사용하여 존재 여부 확인
        if (used.find(required[i]) == used.end()) {
            cout << required[i] << '\n';
            break; // 빠진 재료는 하나이므로 찾으면 즉시 종료
        }
    }

    return 0;
}