// 2292(벌집) 문제 : https://www.acmicpc.net/problem/2292
// 알고리즘 태그 목록
/*
수학
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if(n == 1) cout << 1;
    else if(n > 1) {
        n--;
        int result = 1;
        while(n > 0) {
            n -= 6 * result;
            result++;
        }
        cout << result;
    }

    return 0;
}