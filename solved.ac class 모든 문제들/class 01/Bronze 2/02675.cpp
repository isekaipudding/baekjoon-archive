// 2675(문자열 반복) 문제 : https://www.acmicpc.net/problem/2675
// 알고리즘 태그 목록
/*
구현
문자열
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--) {
        int r;
        cin >> r;
        string s;
        cin >> s;

        int size = s.size();

        for(int i = 0; i < size; i++) {
            char ch = s[i];
            for(int j = 0; j < r; j++) cout << ch;
        }

        cout << '\n';
    }

    return 0;
}