// 2480(주사위 세개) 문제 : https://www.acmicpc.net/problem/2480
// 알고리즘 태그 목록
/*
수학
구현
사칙연산
많은 조건 분기
*/
#include <iostream>

using namespace std;

// 조건문 기초

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c;
    
    cin >> a >> b >> c;
    
    if(a==b && b==c && c==a) cout << 10000 + a * 1000 << '\n';
    if(a==b && b!=c && c!=a) cout << 1000 + a * 100 << '\n';
    if(a!=b && b==c && c!=a) cout << 1000 + b * 100 << '\n';
    if(a!=b && b!=c && c==a) cout << 1000 + c * 100 << '\n';
    if(a!=b && b!=c && c!=a) {
        int result = a;
        if(b > result) result = b;
        if(c > result) result = c;
        cout << result * 100 << '\n';
    }

    return 0;
}