// 2920(문자열 반복) 문제 : https://www.acmicpc.net/problem/2920
// 알고리즘 태그 목록
/*
구현
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char ch[8];
    for(int i = 0; i < 8; i++) {
        char c;
        cin >> c;
        ch[i] = c;
    }

    string s = "";
    for(int i = 0; i < 8; i++) s += ch[i];

    if(s == "12345678") cout << "ascending";
    else if(s == "87654321") cout << "descending";
    else cout << "mixed";

    return 0;
}