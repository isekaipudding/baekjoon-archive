// 28702(FizzBuzz) 문제 : https://www.acmicpc.net/problem/28702
// 알고리즘 태그 목록
/*
수학
문자열
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int value = 0;

    for (int i = 0; i < 3; i++) {
        cin >> s;
        if (isdigit(s[0])) {
            value = stoi(s) + (3 - i);
        }
    }

    if (value % 3 == 0 && value % 5 == 0) {
        cout << "FizzBuzz" << '\n';
    } else if (value % 3 == 0) {
        cout << "Fizz" << '\n';
    } else if (value % 5 == 0) {
        cout << "Buzz" << '\n';
    } else {
        cout << value << '\n';
    }

    return 0;
}