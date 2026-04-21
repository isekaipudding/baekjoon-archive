// 10250(ACM 호텔) 문제 : https://www.acmicpc.net/problem/10250
// 알고리즘 태그 목록
/*
수학
구현
사칙연산
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--) {
        int h, w, n;
        cin >> h >> w >> n;

        int floor = (n - 1) % h + 1;
        int room = (n - 1) / h + 1;
        int result = 100 * floor + room;

        cout << result << '\n';
    }

    return 0;
}