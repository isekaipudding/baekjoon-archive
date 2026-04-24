// 15725(다항함수의 미분) 문제 : https://www.acmicpc.net/problem/15725
// 알고리즘 태그 목록
/*
수학
구현
문자열
많은 조건 분기
파싱
미적분학
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    size_t x_pos = s.find('x');

    if (x_pos == string::npos) {
        cout << "0" << "\n";
    } 
    else {
        string coef = s.substr(0, x_pos);

        if (coef == "") {
            cout << "1" << "\n";
        } else if (coef == "-") {
            cout << "-1" << "\n";
        } else {
            cout << coef << "\n";
        }
    }

    return 0;
}