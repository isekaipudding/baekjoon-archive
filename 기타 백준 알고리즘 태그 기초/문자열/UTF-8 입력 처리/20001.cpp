// 20001(고무오리 디버깅) 문제 : https://www.acmicpc.net/problem/20001
// 알고리즘 태그 목록
/*
구현
utf-8 입력 처리
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int problems = 0;

    getline(cin, s);

    while (getline(cin, s)) {
        if (s == "고무오리 디버깅 끝") {
            break;
        }

        if (s == "문제") {
            problems++;
        } 
        else if (s == "고무오리") {
            if (problems <= 0) {
                problems += 2;
            } else {
                problems--;
            }
        }
    }

    if (problems == 0) {
        cout << "고무오리야 사랑해" << "\n";
    } else {
        cout << "힝구" << "\n";
    }

    return 0;
}