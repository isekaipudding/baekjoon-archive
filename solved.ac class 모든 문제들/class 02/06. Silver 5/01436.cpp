// 1436(영화감독 숌) 문제 : https://www.acmicpc.net/problem/1436
// 알고리즘 태그 목록
/*
브루트포스 알고리즘
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int result = 666;
    int count = 0;

    while (true) {
        string s = to_string(result);
        if (s.find("666") != string::npos) count++;

        if (count == n) {
            cout << result << "\n";
            break;
        }
        
        result++;
    }

    return 0;
}