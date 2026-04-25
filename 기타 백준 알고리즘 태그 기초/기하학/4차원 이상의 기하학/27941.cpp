// 27941(하이퍼 가지 따기) 문제 : https://www.acmicpc.net/problem/27941
// 알고리즘 태그 목록
/*
구현
기하학
4차원 이상의 기하학
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> xor_sum(11, 0);

    for (int i = 0; i < 2047; ++i) {
        for (int j = 0; j < 11; ++j) {
            long long coord;
            cin >> coord;
            xor_sum[j] ^= coord;
        }
    }

    for (int i = 0; i < 11; ++i) {
        cout << xor_sum[i] << (i == 10 ? "" : " ");
    }

    return 0;
}