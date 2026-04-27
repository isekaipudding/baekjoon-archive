// 2720(세탁소 사장 동혁) 문제 : https://www.acmicpc.net/problem/2720
// 알고리즘 태그 목록
/*
수학
그리디 알고리즘
사칙연산
*/
#include <iostream>

using namespace std;

void calculate_change(int cents) {
    // 각 동전의 단위 : 쿼터(25), 다임(10), 니켈(5), 페니(1)
    int quarter = cents / 25;
    cents %= 25;

    int dime = cents / 10;
    cents %= 10;

    int nickel = cents / 5;
    cents %= 5;

    int penny = cents;

    // 결과 출력
    cout << quarter << " " << dime << " " << nickel << " " << penny << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int cents;
        cin >> cents; // 거스름돈(센트 단위) 입력

        // 각 케이스별 동전 개수 계산 및 출력
        calculate_change(cents);
    }

    return 0;
}