// 2753(윤년) 문제 : https://www.acmicpc.net/problem/2753
// 알고리즘 태그 목록
/*
구현
사칙연산
수학
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int year;
    cin >> year;

    if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0) cout << 1;
    else cout << 0;
 
    return 0;
}