// 11880(개미) 문제 : https://www.acmicpc.net/problem/11880
// 알고리즘 태그 목록
/*
수학
기하학
3차원 기하학
피타고라스 정리
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long a, b, c;
        cin >> a >> b >> c;

        long long max_side = max({a, b, c});
        long long sum_others;

        if (max_side == a) {
            sum_others = b + c;
        } else if (max_side == b) {
            sum_others = a + c;
        } else {
            sum_others = a + b;
        }

        long long result = (sum_others * sum_others) + (max_side * max_side);
        
        cout << result << "\n";
    }

    return 0;
}