// 20116(상자의 균형) 문제 : https://www.acmicpc.net/problem/20116
// 알고리즘 태그 목록
/*
수학
누적 합
물리학
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long L;
    cin >> n >> L;

    vector<long long> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    long long suffix_sum = 0;
    bool is_stable = true;

    for (int i = n - 1; i > 0; i--) {
        suffix_sum += x[i];

        long long count = n - i;
        long long left_boundary = count * (x[i - 1] - L);
        long long right_boundary = count * (x[i - 1] + L);

        if (suffix_sum <= left_boundary || suffix_sum >= right_boundary) {
            is_stable = false;
            break;
        }
    }

    if (is_stable) cout << "stable" << endl;
    else cout << "unstable" << endl;

    return 0;
}