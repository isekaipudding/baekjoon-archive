// 9655(돌 게임) 문제 : https://www.acmicpc.net/problem/9655
// 알고리즘 태그 목록
/*
수학
다이나믹 프로그래밍
게임 이론
홀짝성
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 홀짝성은 말 그대로 홀수냐 짝수냐 판정하는 알고리즘입니다.
    if(n & 1) cout << "SK";
    else cout << "CY";

    return 0;
}