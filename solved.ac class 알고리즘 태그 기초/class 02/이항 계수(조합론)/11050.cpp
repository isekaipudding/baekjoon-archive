// 11050(이항 계수 1) 문제 : https://www.acmicpc.net/problem/11050
// 알고리즘 태그 목록
/*
수학
구현
조합론
*/
#include <iostream>

using namespace std;

using ll = long long;

// 팩토리얼 값을 저장할 전역 DP 배열 (n의 최대 범위 10)
// 이 때 fact는 factorial의 줄임말입니다.
ll fact[11];

/**
 * 전역 배열 fact를 채우는 함수 (DP Bottom-Up)
 * 점화식: fact[i] = i * fact[i-1]
 */
void precompute_factorial() {
    fact[0] = 1; // 초기식: 0! = 1
    for (int i = 1; i <= 10; i++) {
        fact[i] = i * fact[i - 1];
    }
}

//  이항 계수 계산하는 함수
ll binomial(int n, int k) {
    if (k < 0 || k > n) return 0;
    // 공식 : n! / (k! * (n-k)!)
    return fact[n] / (fact[k] * fact[n - k]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1. 팩토리얼 테이블 미리 계산
    precompute_factorial();

    // 2. n과 k 입력
    int n, k;
    cin >> n >> k;

    // 3. 결과 출력
    cout << binomial(n, k) << '\n';

    return 0;
}