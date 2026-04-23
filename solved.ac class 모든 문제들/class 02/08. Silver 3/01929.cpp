// 1929(소수 구하기) 문제 : https://www.acmicpc.net/problem/1929
// 알고리즘 태그 목록
/*
수학
정수론
소수 판정
에라토스테네스의 체
*/
#include <bits/stdc++.h>

using namespace std;

vector<bool> sieve(int limit) {
    vector<bool> is_prime(limit + 1, true);

    if (limit >= 0) is_prime[0] = false;
    if (limit >= 1) is_prime[1] = false;

    for (long long i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (long long j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<bool> primes = sieve(n);

    for(int i = m; i <= n; i++) {
        if(primes[i]) cout << i << '\n';
    }

    return 0;
}