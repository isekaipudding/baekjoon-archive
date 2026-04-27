// 13777(Hunt The Rabbit) 문제 : https://www.acmicpc.net/problem/13777
// 알고리즘 태그 목록
/*
구현
이분 탐색
*/
#include <iostream>

using namespace std;

// 이분 탐색 함수
// 이분 탐색은 주어진 문제마다 함수 형태가 좀 달라지나 이게 가장 기본이라고 보시면 됩니다.
// 정석은 low = 0, high = array.size() - 1 등으로 되어 있으나 여기서는 low, high가 고정되어 있습니다.
// 문제에서 토끼(숫자)를 발견할 때마다 출력하는 방식입니다.
void binary_search(int target) {
    int low = 1;
    int high = 50;

    while (low <= high) {
        // 중간값 계산 (이분 탐색의 핵심)
        int mid = (low + high) / 2;

        // 현재 시도한 숫자 출력
        cout << mid << " ";

        if (mid == target) {
            // 목표를 찾으면 루프 종료
            break;
        } else if (mid < target) {
            // 목표보다 작으면 오른쪽 범위 탐색
            low = mid + 1;
        } else {
            // 목표보다 크면 왼쪽 범위 탐색
            high = mid - 1;
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    // 무한 루프 내에서 입력을 받고 0이면 종료하는 구조
    while (true) {
        cin >> n;
        
        if (n == 0) {
            break;
        }

        // 각 숫자(토끼)에 대해 이분 탐색 경로 출력
        binary_search(n);
    }

    return 0;
}