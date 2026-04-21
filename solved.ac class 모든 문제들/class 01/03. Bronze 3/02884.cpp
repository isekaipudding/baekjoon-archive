// 2884(알람 시계) 문제 : https://www.acmicpc.net/problem/2884
// 알고리즘 태그 목록
/*
수학
사칙연산
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, m;
    cin >> h >> m;

    int time = 60 * h + m;
    time -= 45;

    if(time < 0) time += 60 * 24;

    cout << time / 60 << " " << time % 60;

    return 0;
}