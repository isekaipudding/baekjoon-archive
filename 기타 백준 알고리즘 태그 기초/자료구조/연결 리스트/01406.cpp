// 1406(에디터) 문제 : https://www.acmicpc.net/problem/1406
// 알고리즘 태그 목록
/*
자료 구조
스택
연결 리스트
*/
#include <bits/stdc++.h>
 
using namespace std;

vector<char> L;
vector<char> R;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int size = s.size();

    for(int i = 0; i < size; i++) L.push_back(s[i]);

    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        char cmd;
        cin >> cmd;

        switch(cmd) {
            case 'L' :
                if(!L.empty()) {
                    char ch = L.back();
                    L.pop_back();
                    R.push_back(ch);
                }
                break;
            case 'D' :
                if(!R.empty()) {
                    char ch = R.back();
                    R.pop_back();
                    L.push_back(ch);
                }
                break;
            case 'B' :
                if(!L.empty()) L.pop_back();
                break;
            case 'P' :
                char ch;
                cin >> ch;
                L.push_back(ch);
                break;
            default :
                break;
        }
    }

    int L_size = L.size();
    int R_size = R.size();

    for(int i = 0; i < L_size; i++) cout << L[i];
    for(int i = R_size - 1; i > -1; i--) cout << R[i];

    return 0;
}