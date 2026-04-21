// 9498(시험 성적) 문제 : https://www.acmicpc.net/problem/9498
// 알고리즘 태그 목록
/*
구현
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int score; cin >> score;
    
    switch(score/10) {
        case 10:
            cout << "A" << '\n';
            break;
        case 9:
            cout << "A" << '\n';
            break;
        case 8:
            cout << "B" << '\n';
            break;
        case 7:
            cout << "C" << '\n';
            break;
        case 6:
            cout << "D" << '\n';
            break;
        default:
            cout << "F" << '\n';
            break;
    }
 
    return 0;
}