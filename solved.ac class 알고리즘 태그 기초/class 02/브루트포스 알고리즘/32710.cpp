// 32710(구구단표) 문제 : https://www.acmicpc.net/problem/32710
// 알고리즘 태그 목록
/*
수학
구현
브루트포스 알고리즘
사칙연산
*/
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 1. 구구단의 '단(a)' 혹은 '곱하는 수(b)'에 포함되는지 확인
    // 구구단은 2~9단, 곱하는 수는 1~9이므로 1부터 9까지의 수는 무조건 표에 등장함
    if (n >= 1 && n <= 9) {
        cout << 1 << '\n';
        return 0;
    }

    // 2. 구구단의 '결과값(a * b)' 중에 n이 있는지 확인 (브루트포스 탐색)
    // 외워둔 구구단을 전수 조사하는 방식입니다.
    for (int a = 2; a <= 9; ++a) {
        for (int b = 1; b <= 9; ++b) {
            if (a * b == n) {
                // n이 결과값으로 존재한다면 1 출력 후 즉시 종료
                cout << 1 << '\n';
                return 0;
            }
        }
    }

    // 3. 위의 모든 조건에 해당하지 않으면 구구단표에 없는 수임
    cout << 0 << '\n';

    return 0;
}