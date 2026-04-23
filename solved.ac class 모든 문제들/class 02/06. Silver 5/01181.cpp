// 1181(단어 정렬) 문제 : https://www.acmicpc.net/problem/1181
// 알고리즘 태그 목록
/*
문자열
정렬
*/
#include <bits/stdc++.h>

using namespace std;

const int limit = 20000;

string word[limit];

bool compare(const string &a, const string &b) {
    if (a.length() != b.length()) return a.length() < b.length();
    return a < b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for(int i = 0; i < n; i++) cin >> word[i];

    sort(word, word + n, compare);

    for(int i = 0; i < n; i++) {
        if (i > 0 && word[i] == word[i - 1]) continue;
        cout << word[i] << "\n";
    }

    return 0;
}