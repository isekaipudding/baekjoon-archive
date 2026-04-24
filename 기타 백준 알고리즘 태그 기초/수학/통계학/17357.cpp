// 17357(자동차가 차주 김표준의 편을 들면?) 문제 : https://www.acmicpc.net/problem/17357
// 알고리즘 태그 목록
/*
수학
브루트포스 알고리즘
누적 합
통계학
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> A(N + 1);
    vector<ll> prefix1(N + 1, 0);
    vector<ll> prefix2(N + 1, 0);

    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        prefix1[i] = prefix1[i - 1] + A[i];
        prefix2[i] = prefix2[i - 1] + (A[i] * A[i]);
    }

    for (int k = 1; k <= N; ++k) {
        ll max_value = -1;
        int best_index = 1;

        for (int i = 1; i <= N - k + 1; ++i) {
            ll s1 = prefix1[i + k - 1] - prefix1[i - 1];
            ll s2 = prefix2[i + k - 1] - prefix2[i - 1];

            ll current_value = k * s2 - s1 * s1;

            if (current_value > max_value) {
                max_value = current_value;
                best_index = i;
            }
        }
        cout << best_index << "\n";
    }

    return 0;
}