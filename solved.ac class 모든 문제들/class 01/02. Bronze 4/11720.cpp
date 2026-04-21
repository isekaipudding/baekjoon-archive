// 11720(숫자의 합) 문제 : https://www.acmicpc.net/problem/11720
// 알고리즘 태그 목록
/*
구현
수학
문자열
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string s;
    cin >> s;

    int result = 0;

    for(int i = 0; i < n; i++) {
        result += s[i] - '0';
    }

    cout << result;

    return 0;
}