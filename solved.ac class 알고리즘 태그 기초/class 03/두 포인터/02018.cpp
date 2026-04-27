// 2018(수들의 합 5) 문제 : https://www.acmicpc.net/problem/2018
// 알고리즘 태그 목록
/*
수학
두 포인터
*/
#include <iostream>

using namespace std;

// 합(sum) 계산 시 int 범위를 초과하므로 별칭 사용
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int start = 1, end = 1;
    ll current_sum = 1;
    int count = 0;

    // 두 포인터가 범위를 벗어나지 않을 때까지 반복
    while (start <= end && end <= n) {
        if (current_sum == n) {
            count++;
            // 다음 경우를 찾기 위해 end를 확장
            end++;
            current_sum += end;
        } else if (current_sum < n) {
            // 합이 부족하면 end를 오른쪽으로 이동
            end++;
            current_sum += end;
        } else {
            // 합이 넘치면 start가 가리키던 값을 빼고 start를 오른쪽으로 이동
            current_sum -= start;
            start++;
        }
    }

    cout << count << "\n";

    return 0;
}