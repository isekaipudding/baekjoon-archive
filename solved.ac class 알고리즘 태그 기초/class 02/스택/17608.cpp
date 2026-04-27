// 17608(막대기) 문제 : https://www.acmicpc.net/problem/17608
// 알고리즘 태그 목록
/*
구현
자료 구조
스택
*/
#include <iostream>
#include <vector>

using namespace std;

// 막대기 개수 계산해주는 함수
int count_visible_sticks(const vector<int>& sticks) {
    if (sticks.empty()) return 0;

    int visible_count = 0;
    int max_height = 0;

    // 벡터의 맨 뒤(오른쪽)부터 앞으로 순회하며 확인
    // 맨 오른쪽 막대기는 항상 보이며, 그보다 높은 막대기만 새로 보임
    for (int i = sticks.size() - 1; i >= 0; i--) { // 역순 루프
        if (sticks[i] > max_height) {
            visible_count++;
            max_height = sticks[i]; // 현재까지의 최대 높이 갱신
        }
    }

    return visible_count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n; // 막대기 개수 입력

    // vector를 스택처럼 사용하여 모든 막대기 높이 저장
    vector<int> sticks(n);
    for (int i = 0; i < n; i++) {
        cin >> sticks[i];
    }

    // 결과 계산 및 출력
    cout << count_visible_sticks(sticks) << '\n';

    return 0;
}