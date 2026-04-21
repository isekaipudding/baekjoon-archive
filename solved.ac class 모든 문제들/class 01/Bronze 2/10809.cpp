// 10809(알파벳 찾기) 문제 : https://www.acmicpc.net/problem/10809
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

    int alphabet[26];
    for(int i = 0; i < 26; i++) alphabet[i] = -1;


    string s;
    cin >> s;

    int size = s.size();

    for(int i = 0; i < size; i++) {
        char ch = s[i] - 'a';
        int index = ch;

        if(alphabet[index] == -1) alphabet[index] = i;
    }

    for(int i = 0; i < 26; i++) cout << alphabet[i] << " ";

    return 0;
}