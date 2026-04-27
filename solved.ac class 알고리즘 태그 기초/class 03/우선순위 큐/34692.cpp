// 34692(아 마이마이 하고 싶다) 문제 : https://www.acmicpc.net/problem/34692
// 알고리즘 태그 목록
/*
구현
자료 구조
우선순위 큐
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    // C++의 priority_queue는 기본이 최대 힙입니다.
    // 최소 힙을 만들기 위해 greater<int>를 사용합니다.
    priority_queue<int, vector<int>, greater<int>> pq;

    // 처음에는 모든 기기의 대기 시간이 0입니다.
    for (int i = 0; i < m; i++) {
        pq.push(0);
    }

    // n명의 사람들이 순서대로 기기를 선택
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;

        // 1. 가장 짧은 대기 시간을 가진 기기를 꺼냄
        int min_wait = pq.top();
        pq.pop();

        // 2. 해당 기기에 플레이 시간 추가 후 다시 삽입
        pq.push(min_wait + t);
    }

    // n명이 모두 배정된 후, 다시 가장 짧은 대기 시간이 코이가 기다릴 시간입니다.
    int koi_wait = pq.top();

    if (koi_wait <= k) {
        cout << "WAIT" << '\n';
    } else {
        cout << "GO" << '\n';
    }

    return 0;
}