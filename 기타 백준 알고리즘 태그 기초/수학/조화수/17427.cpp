// 17427(약수의 합 2) 문제 : https://www.acmicpc.net/problem/17427
// 알고리즘 태그 목록
/*
수학
정수론
조화수
*/
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    ll result = 0;
    
    for (int i = 1; i <= N; ++i) result += (ll)i * (N / i);

    cout << result << "\n";

    return 0;
}