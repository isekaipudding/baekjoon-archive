// 13171(A) 문제 : https://www.acmicpc.net/problem/13171
// 알고리즘 태그 목록
/*
수학
분할 정복을 이용한 거듭제곱
*/
#include <iostream>

using namespace std;

using ll = long long;

// 이것 바로 분할 정복을 이용한 거듭제곱!
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll A, X;
    
    // A : 밑(base), X : 지수(exponent)
    cin >> A >> X;

    // 분리된 함수를 호출하여 결과 출력(A^X mod 1000000007)
    cout << mod_pow(A, X, 1000000007) << "\n";

    return 0;
}