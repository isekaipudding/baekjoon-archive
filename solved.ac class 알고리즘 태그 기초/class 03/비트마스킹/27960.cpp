// 27960(사격 내기) 문제 : https://www.acmicpc.net/problem/27960
// 알고리즘 태그 목록
/*
수학
비트마스킹
*/
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;

    // A와 B 중 한 명만 맞힌 과녁의 합 = A XOR B
    int c = a ^ b;

    cout << c << "\n";

    return 0;
}