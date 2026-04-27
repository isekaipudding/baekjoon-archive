// 2435(기상청 인턴 신현수) 문제 : https://www.acmicpc.net/problem/2435
// 알고리즘 태그 목록
/*
구현
브루트포스 알고리즘
누적 합
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // 누적 합을 저장할 배열 (1-based index가 계산하기 편합니다.)
    int prefix[101] = {0};

    for (int i = 1; i <= n; i++) {
        int temp;
        cin >> temp;
        // i번째까지의 합 = (i-1번째까지의 합) + 현재 온도
        prefix[i] = prefix[i - 1] + temp;
    }

    // 온도의 합이 음수가 될 수 있으므로 아주 작은 값으로 초기화
    int max_sum = -1e9;

    // k일 연속된 구간의 합 계산 (i는 구간의 끝점)
    for (int i = k; i <= n; i++) {
        // i-k+1 번째부터 i 번째까지의 합
        int current_sum = prefix[i] - prefix[i - k];
        
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    cout << max_sum << "\n";

    return 0;
}