// 10987(모음의 개수) 문제 : https://www.acmicpc.net/problem/10987
// 알고리즘 태그 목록
/*
구현
문자열
*/
#include <iostream>
#include <string>
 
using namespace std;

// 문자열 기초
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int a = 0;
    int e = 0;
    int i = 0;
    int o = 0;
    int u = 0;

    int size = s.size();

    // 이미 변수 i 사용해서 index로 대체
    for(int index = 0; index < size; index++) {
        if(s[index] == 'a') a++;
        if(s[index] == 'e') e++;
        if(s[index] == 'i') i++;
        if(s[index] == 'o') o++;
        if(s[index] == 'u') u++;
    }

    int result = a + e + i + o + u;

    cout << result;

    return 0;
}