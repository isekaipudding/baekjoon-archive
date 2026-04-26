// 33572(자세히 보아야 예쁘다) 문제 : https://www.acmicpc.net/problem/33572
// 알고리즘 태그 목록
/*
구현
그리디 알고리즘
비둘기집 원리
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long M;
    cin >> N >> M;

    long long total_safe_capacity = 0;
    for (int i = 0; i < N; i++) {
        long long A;
        cin >> A;
        total_safe_capacity += (A - 1);
    }

    if (total_safe_capacity >= M) {
        cout << "DIMI" << '\n';
    } else {
        cout << "OUT" << '\n';
    }

    return 0;
}