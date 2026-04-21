// 2439(별 찍기 - 2) 문제 : https://www.acmicpc.net/problem/2439
// 알고리즘 태그 목록
/*
구현
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < n - i; j++) cout << " ";
        for(int j = 0; j < i; j++) cout << "*";
        cout << "\n";
    }

    return 0;
}