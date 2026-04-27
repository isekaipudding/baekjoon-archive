// 8723(Patyki) 문제 : https://www.acmicpc.net/problem/8723
// 알고리즘 태그 목록
/*
수학
기하학
사칙연산
피타고라스 정리
*/
#include <iostream>
 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 세 변의 길이를 입력 받습니다.
    int a, b, c;
    cin >> a >> b >> c;

    if(a == b && b == c) {
        cout << 2;
        return 0;
    }

    // x : 가장 짧은 변
    // y : 중간 길이 변
    // z : 가장 긴 변
    int z = a;
    z = (b > z) ? b : z;
    z = (c > z) ? c : z;

    int x = a;
    x = (b < x) ? b : x;
    x = (c < x) ? c : x;

    int y = (a + b + c) - z - x;

    // 피타고라스 정리 : x^2 + y^2 = z^2이면 직각삼각형이고 역으로도 성립한다.
    if(x * x + y * y == z * z) cout << 1;
    else cout << 0;

    return 0;
}