// 22984(반짝반짝 2) 문제 : https://www.acmicpc.net/problem/22984
// 알고리즘 태그 목록
/*
수학
확률론
기댓값의 선형성
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<double> p(N);
    for (int i = 0; i < N; ++i) {
        cin >> p[i];
    }

    double total_expectation = 0;

    for (int i = 0; i < N; ++i) {
        total_expectation += p[i];
    }

    for (int i = 0; i < N - 1; ++i) {
        total_expectation += p[i] * (1.0 - p[i + 1]) + (1.0 - p[i]) * p[i + 1];
    }

    cout << fixed << setprecision(10) << total_expectation << "\n";

    return 0;
}