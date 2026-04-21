// 1978(소수 찾기) 문제 : https://www.acmicpc.net/problem/1978
// 알고리즘 태그 목록
/*
소수 판정
정수론
수학
*/
#include <bits/stdc++.h>
 
using namespace std;

bool is_prime(int n) {
    if (n < 2) return false;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    int result = 0;
    while(t--) {
        int n;
        cin >> n;

        if(is_prime(n)) result++;
    }

    cout << result;

    return 0;
}