// 14626(ISBN) 문제 : https://www.acmicpc.net/problem/14626
// 알고리즘 태그 목록
/*
수학
구현
브루트포스 알고리즘
사칙연산
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string isbn;
    cin >> isbn;

    int index = -1;
    for (int i = 0; i < 13; i++) {
        if (isbn[i] == '*') {
            index = i;
            break;
        }
    }

    for (int digit = 0; digit <= 9; digit++) {
        int sum = 0;
        for (int i = 0; i < 13; i++) {
            int value;
            if (i == index) {
                value = digit;
            } else {
                value = isbn[i] - '0';
            }

            if (i % 2 == 0) sum += value * 1;
            else sum += value * 3;
        }

        if (sum % 10 == 0) {
            cout << digit << '\n';
            break;
        }
    }

    return 0;
}