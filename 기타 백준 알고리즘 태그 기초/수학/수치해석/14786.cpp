// 14786(Ax+Bsin(x)=C 2) 문제 : https://www.acmicpc.net/problem/14786
// 알고리즘 태그 목록
/*
수학
이분 탐색
수치해석
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double A, B, C;
    cin >> A >> B >> C;

    double low = (C - B) / A;
    double high = (C + B) / A;

    for (int i = 0; i < 100; ++i) {
        double mid = (low + high) / 2.0;
        double value = A * mid + B * sin(mid);

        if (value < C) {
            low = mid;
        } else {
            high = mid;
        }
    }

    cout << fixed << setprecision(19) << low << "\n";

    return 0;
}