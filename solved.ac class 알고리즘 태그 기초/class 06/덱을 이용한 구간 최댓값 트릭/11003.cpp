// 11003(최솟값 찾기) 문제 : https://www.acmicpc.net/problem/11003
// 알고리즘 태그 목록
/*
자료 구조
우선순위 큐
덱
덱을 이용한 구간 최댓값 트릭
*/
#include <iostream>
#include <deque>
#include <vector>

using namespace std;

// 데이터와 인덱스를 함께 저장하기 위한 구조체
struct Node {
    int value;
    int index;
};

int main() {
    // 1. 입출력 최적화 (필수)
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, L;
    cin >> N >> L;

    // 단조 증가 덱 선언
    deque<Node> dq;

    for (int i = 0; i < N; i++) {
        int now;
        cin >> now;

        // [Step 1] 윈도우 범위를 벗어난 오래된 값 제거
        // i-L+1 이 시작점이므로, 인덱스가 i-L 이하인 것은 버림
        if (!dq.empty() && dq.front().index <= i - L) {
            dq.pop_front();
        }

        // [Step 2] 현재 값(now)보다 큰 값들은 덱 뒤에서 제거
        // 나(now)보다 크면서 나보다 먼저 들어온 애들은 절대 최솟값이 될 수 없음
        while (!dq.empty() && dq.back().value >= now) {
            dq.pop_back();
        }

        // [Step 3] 현재 노드 삽입
        dq.push_back({now, i});

        // [Step 4] 덱의 맨 앞이 항상 현재 구간의 최솟값
        cout << dq.front().value << " ";
    }

    return 0;
}