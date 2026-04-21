// 2231(분해합) 문제 : https://www.acmicpc.net/problem/2231
// 알고리즘 태그 목록
/*
브루트포스 알고리즘
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int result = -1;
    bool status = false;

    string s = to_string(n);
    int size = s.length();

    int start = n - (9 * size);
    if (start < 1) start = 1;

    for (int i = start; i < n; i++) {
        int temp = i;
        int value = i;

        while (value) {
            temp += value % 10;
            value /= 10;
        }

        if (temp == n) {
            result = i;
            status = true;
            break;
        }
    }

    if (status) cout << result << '\n';
    else cout << 0 << '\n';

    return 0;
}