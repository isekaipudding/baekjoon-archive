// 4233(가짜소수) 문제 : https://www.acmicpc.net/problem/4233
// 알고리즘 태그 목록
/*
수학
정수론
소수 판정
분할 정복을 이용한 거듭제곱
페르마의 소정리
*/
#include <iostream>

using namespace std;

using ll = long long;

ll mod_pow(ll base, ll exponent, ll mod) {
    ll result = 1;
    base = base % mod; // 초기값부터 나머지 연산 적용

    while (exponent) {
        // 지수가 홀수라면 현재의 base를 결과에 곱함
        if (exponent & 1) {
            result = (result * base) % mod;
        }
        // base를 제곱하여 다음 단계로 준비 (A^1 -> A^2 -> A^4 -> A^8 ...)
        base = (base * base) % mod;
        // 지수를 절반으로 줄임
        exponent >>= 1;
    }
    return result;
}

bool is_prime(ll n) {
    if (n <= 1) return false;
    if (n == 2) return true; // 2는 유일한 짝수 소수
    if (n % 2 == 0) return false; // 2를 제외한 짝수 미리 거르기

    // i < n 대신 i * i <= n (즉, 루트 n) 까지만 확인
    for (ll i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll p, a;
    while (true) {
        cin >> p >> a;
        // 종료 조건
        if (p == 0 && a == 0) break;

        // 1. p가 소수인지 먼저 확인
        // 페르마의 소정리는 소수일 때 '항상' 성립하므로, 
        // 문제에서 요구하는 '가짜' 소수가 되려면 p는 반드시 합성수여야 합니다.
        if (is_prime(p)) {
            cout << "no" << "\n";
        } else {
            // 2. 합성수일 때 a^p ≡ a (mod p) 가 성립하는지 확인
            if (mod_pow(a, p, p) == a) {
                cout << "yes" << "\n";
            } else {
                cout << "no" << "\n";
            }
        }
    }

    return 0;
}