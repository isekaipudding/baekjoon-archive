// 1792(공약수) 문제 : https://www.acmicpc.net/problem/1792
// 알고리즘 태그 목록
/*
수학
정수론
누적 합
포함 배제의 원리
조화수
뫼비우스 반전 공식
*/
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAX = 50005;
int mu[MAX];
int psum_mu[MAX];

void sieve() {
    mu[1] = 1;
    for (int i = 1; i < MAX; ++i) {
        for (int j = 2 * i; j < MAX; j += i) {
            mu[j] -= mu[i];
        }
    }
    
    for (int i = 1; i < MAX; ++i) {
        psum_mu[i] = psum_mu[i - 1] + mu[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    int N;
    cin >> N;

    while (N--) {
        int a, b, d;
        cin >> a >> b >> d;

        int A = a / d;
        int B = b / d;
        int limit = min(A, B);
        
        ll result = 0;
        
        for (int i = 1, j; i <= limit; i = j + 1) {
            j = min(A / (A / i), B / (B / i));
            
            ll mu_sum = psum_mu[j] - psum_mu[i - 1];
            
            result += mu_sum * (A / i) * (B / i);
        }
        
        cout << result << "\n";
    }

    return 0;
}