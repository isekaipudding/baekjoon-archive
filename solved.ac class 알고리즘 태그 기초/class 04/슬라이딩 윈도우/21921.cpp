// 21921(블로그) 문제 : https://www.acmicpc.net/problem/21921
// 알고리즘 태그 목록
/*
누적 합
슬라이딩 윈도우
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, X;
    cin >> N >> X;

    vector<int> visitors(N);
    for (int i = 0; i < N; ++i) {
        cin >> visitors[i];
    }

    // 초기 윈도우(첫 X일간의 합) 설정
    long long current_sum = 0;
    for (int i = 0; i < X; ++i) {
        current_sum += visitors[i];
    }

    long long max_sum = current_sum;
    int count = 1;

    // 슬라이딩 윈도우 시작
    // i는 윈도우에 새롭게 추가되는 요소의 인덱스
    for (int i = X; i < N; ++i) {
        // 윈도우 이동: 새 값 더하고, 가장 오래된 값 빼기
        current_sum += visitors[i];
        current_sum -= visitors[i - X];

        if (current_sum > max_sum) {
            max_sum = current_sum;
            count = 1; // 새로운 최댓값 발견 시 카운트 초기화
        } else if (current_sum == max_sum) {
            count++; // 최댓값과 같은 경우 카운트 증가
        }
    }

    // 결과 출력
    if (max_sum == 0) {
        cout << "SAD" << "\n";
    } else {
        cout << max_sum << "\n";
        cout << count << "\n";
    }

    return 0;
}