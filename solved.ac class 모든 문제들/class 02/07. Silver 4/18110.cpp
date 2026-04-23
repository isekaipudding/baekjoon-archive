// 18110(solved.ac) 문제 : https://www.acmicpc.net/problem/18110
// 알고리즘 태그 목록
/*
수학
구현
정렬
*/
#include <bits/stdc++.h>

using namespace std;

int custom_round(double value) {
    return (int)floor(value + 0.5);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n == 0) {
        cout << 0 << "\n";
        return 0;
    }

    vector<int> L(n);
    
    for (int i = 0; i < n; i++)
        cin >> L[i];

    sort(L.begin(), L.end());

    int trim = custom_round(n * 0.15);

    double sum = 0;
    for (int i = trim; i < n - trim; i++) {
        sum += L[i];
    }

    int remaining_count = n - (2 * trim);
    cout << custom_round(sum / remaining_count) << "\n";

    return 0;
}