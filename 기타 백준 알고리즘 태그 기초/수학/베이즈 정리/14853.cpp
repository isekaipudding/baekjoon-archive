// 14853(동전 던지기) 문제 : https://www.acmicpc.net/problem/14853
// 알고리즘 태그 목록
/*
수학
조합론
확률론
미적분학
베이즈 정리
*/
#include <bits/stdc++.h>

using namespace std;

double ln_fact[2005];

double ln_binomial(int n, int k) {
    if (k < 0 || k > n) return -1e18;
    return ln_fact[n] - ln_fact[k] - ln_fact[n - k];
}

void precompute() {
    ln_fact[0] = 0;
    for (int i = 1; i <= 2002; ++i) {
        ln_fact[i] = ln_fact[i - 1] + log(i);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int T;
    cin >> T;

    while (T--) {
        int n1, m1, n2, m2;
        cin >> n1 >> m1 >> n2 >> m2;

        int a = m1 + 1;
        int b = n1 - m1 + 1;

        double total_prob = 0.0;

        for (int k = 0; k <= m2; ++k) {
            double ln_term = ln_binomial(n2 + 1, k) 
                             + ln_fact[a + k - 1] 
                             + ln_fact[b + n2 - k] 
                             + ln_fact[a + b - 1]
                             - ln_fact[a - 1] 
                             - ln_fact[b - 1] 
                             - ln_fact[a + b + n2];

            total_prob += exp(ln_term);
        }

        cout << fixed << setprecision(10) << total_prob << "\n";
    }

    return 0;
}