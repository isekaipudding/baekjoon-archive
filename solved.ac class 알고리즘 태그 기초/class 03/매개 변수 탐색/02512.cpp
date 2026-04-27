// 2512(예산) 문제 : https://www.acmicpc.net/problem/2512
// 알고리즘 태그 목록
/*
이분 탐색
매개 변수 탐색
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> requests(n);
    int low = 0, high = 0;

    for (int i = 0; i < n; ++i) {
        cin >> requests[i];
        if (requests[i] > high) high = requests[i]; // 요청 중 최댓값을 high로 설정
    }

    int m;
    cin >> m;

    int result = 0;

    // 이분 탐색을 이용한 매개 변수 탐색 시작
    while (low <= high) {
        int mid = (low + high) / 2;
        int current_sum = 0;

        for (int i = 0; i < n; ++i) {
            // 상한액(mid)보다 크면 상한액만큼, 작으면 요청만큼 배정
            if (requests[i] > mid) current_sum += mid;
            else current_sum += requests[i];
        }

        /* [초보자를 위한 핵심 주석]
           단순히 mid가 m과 같은지 찾는 것이 아니라, 
           "current_sum <= m"이라는 조건을 만족하는 '최댓값'을 찾는 과정입니다.
           조건을 만족하더라도(Yes), 더 큰 상한액이 가능할 수 있으므로 result를 기록하고 
           범위를 오른쪽(더 큰 값)으로 계속 좁혀나가는 것, 이것이 매개 변수 탐색입니다.
        */
        if (current_sum <= m) {
            result = mid; // 우선 현재 mid는 가능하므로 저장
            low = mid + 1; // 더 큰 상한액이 가능한지 확인
        } else {
            high = mid - 1; // 예산 초과이므로 상한액을 줄여야 함
        }
    }

    cout << result << "\n";

    return 0;
}