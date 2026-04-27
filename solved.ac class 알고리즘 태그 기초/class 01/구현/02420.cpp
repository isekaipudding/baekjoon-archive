// 2420(사파리월드) 문제 : https://www.acmicpc.net/problem/2420
// 알고리즘 태그 목록
/*
수학
구현
사칙연산
*/
#include <iostream>
 
using namespace std;

// 정수 기초
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 범위가 크므로 int가 아닌 long long을 써야 합니다.
    long long a, b;
    cin >> a >> b;
    
    cout << abs(a - b);
 
    return 0;
}