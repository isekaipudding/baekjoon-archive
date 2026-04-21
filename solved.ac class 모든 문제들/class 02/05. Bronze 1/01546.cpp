// 1546(평균) 문제 : https://www.acmicpc.net/problem/1546
// 알고리즘 태그 목록
/*
수학
사칙연산
*/
#include <bits/stdc++.h>

using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int scores[1000]; 
    int max_value = 0;
    int sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> scores[i];
        if (scores[i] > max_value) max_value = scores[i];
        sum += scores[i];
    }

    cout << fixed;
    cout.precision(10);

    double result = (double)sum * 100 / max_value / n;
    cout << result << '\n';

    return 0;
}