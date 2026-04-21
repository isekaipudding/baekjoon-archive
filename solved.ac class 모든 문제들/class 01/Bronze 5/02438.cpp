// 2438(별 찍기 - 1) 문제 : https://www.acmicpc.net/problem/2438
// 알고리즘 태그 목록
/*
구현
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) cout << "*";
        cout << '\n';
    }
 
    return 0;
}