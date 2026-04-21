// 2869(달팽이는 올라가고 싶다) 문제 : https://www.acmicpc.net/problem/2869
// 알고리즘 태그 목록
/*
수학
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int climb, slip, height;
    cin >> climb >> slip >> height;

    int day = 0;

    if(climb > height) day = 1;
    else day = 1 + ceil((double)(height-climb)/(climb-slip));

    cout << day;

    return 0;
}