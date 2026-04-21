// 8958(OX퀴즈) 문제 : https://www.acmicpc.net/problem/8958
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
        string ox;
        cin >> ox;

        int count = 0;
        int size = ox.size();

        int result = 0;

        for(int i = 0; i < size; i++) {
            if(ox[i] == 'O') {
                count++;
                result += count;
            } else count = 0;
        }

        cout << result << '\n';
    }

    return 0;
}