// 17206(준석이의 수학 숙제) 문제 : https://www.acmicpc.net/problem/17206
// 알고리즘 태그 목록
/*
수학
포함 배제의 원리
*/
#include <iostream>

using namespace std;

using ll = long long;

/**
 * n 이하의 k의 배수들의 총합을 구하는 함수
 * 등차수열의 합 공식 활용: k * (m * (m + 1) / 2)
 */
ll get_multiple_sum(int n, int k) {
    ll m = n / k; // n 이하의 k의 배수 개수
    return k * (m * (m + 1) / 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        // 포함 배제의 원리를 명시적으로 작성
        ll sum3 = get_multiple_sum(N, 3);   // 3의 배수의 합
        ll sum7 = get_multiple_sum(N, 7);   // 7의 배수의 합
        ll sum21 = get_multiple_sum(N, 21); // 21(3과 7의 최소공배수)의 배수의 합

        // 3의 배수와 7의 배수를 더한 뒤, 중복 계산된 21의 배수를 뺌
        ll result = sum3 + sum7 - sum21;

        cout << result << "\n";
    }

    return 0;
}