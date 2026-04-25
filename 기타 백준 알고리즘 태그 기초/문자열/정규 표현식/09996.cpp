// 9996(한국이 그리울 땐 서버에 접속하지) 문제 : https://www.acmicpc.net/problem/9996
// 알고리즘 태그 목록
/*
문자열
정규 표현식
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string pattern;
    cin >> pattern;

    int pos = pattern.find('*');
    string pre = pattern.substr(0, pos);
    string suf = pattern.substr(pos + 1);

    string regex_str = "^" + pre + ".*" + suf + "$";
    regex re(regex_str);

    for (int i = 0; i < n; ++i) {
        string filename;
        cin >> filename;

        if (regex_match(filename, re)) {
            cout << "DA\n";
        } else {
            cout << "NE\n";
        }
    }

    return 0;
}