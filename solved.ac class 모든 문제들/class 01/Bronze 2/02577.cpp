// 2577(숫자의 개수) 문제 : https://www.acmicpc.net/problem/2577
// 알고리즘 태그 목록
/*
수학
구현
사칙연산
*/
#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c;
    cin >> a >> b >> c;

    string s = to_string(a * b * c);
    int size = s.size();

    for(int i = 0; i < 10; i++) {
        int result = 0;
        char ch = 48 + i;

        for(int j = 0; j < size; j++) {
            if(s[j] == ch) result++;
        }

        cout << result << '\n';
    }

    return 0;
}