// 3052(나머지) 문제 : https://www.acmicpc.net/problem/3052
// 알고리즘 태그 목록
/*
수학
집합과 맵
사칙연산
*/
#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool check[42];
    for(int i = 0; i < 42; i++) check[i] = false;

    for(int i = 0; i < 10; i++) {
        int n;
        cin >> n;
        check[n % 42] = true;
    }

    int result = 0;
    for(int i = 0; i < 42; i++) {
        if(check[i]) result++;
    }

    cout << result;

    return 0;
}