// 10952(A+B - 5) 문제 : https://www.acmicpc.net/problem/10952
// 알고리즘 태그 목록
/*
구현
사칙연산
수학
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(true) {
        int a, b;
        cin >> a >> b;
    
        if(a == 0 && b == 0) break;
    
        cout << a + b << "\n";	
    }

    return 0;
}