// 4355(서로소) 문제 : https://www.acmicpc.net/problem/4355
// 알고리즘 태그 목록
/*
수학
정수론
오일러 피 함수
*/
#include <iostream>

using namespace std;

using ll = long long;

/**
 * n의 오일러 피 함수 값을 구하는 함수
 * 시간 복잡도: O(sqrt(n))
 */
ll get_phi(ll n) {
    if (n == 1) return 0; // 문제 조건: n보다 작은 양의 정수

    ll result = n;
    
    // 2부터 sqrt(n)까지 소인수 탐색
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            // p가 n의 소인수인 경우 공식 적용
            result = result - (result / p);
            
            // n에서 해당 소인수를 모두 제거
            while (n % p == 0) {
                n /= p;
            }
        }
    }

    // 소인수 분해 후 남은 n이 1보다 크면, 그 남은 n도 소수임
    if (n > 1) {
        result = result - (result / n);
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    while (cin >> n && n) {
        cout << get_phi(n) << "\n";
    }

    return 0;
}