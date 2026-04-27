// 15995(잉여역수 구하기) 문제 : https://www.acmicpc.net/problem/15995
// 알고리즘 태그 목록
/*
수학
브루트포스 알고리즘
정수론
모듈로 곱셈 역원
*/
#include <iostream>

using namespace std;

/**
 * 모듈로 곱셈 역원 기초
 * (a * x) % m == 1 을 만족하는 최소의 양의 정수 x를 찾습니다.
 * 문제의 제약 조건(a, m <= 10,000)이 작으므로 선형 탐색으로 해결 가능합니다.
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, m;
    cin >> a >> m;

    // x는 1부터 m까지 확인하면 충분합니다.
    // (역원이 존재한다면 m 미만에서 반드시 발견됨)
    for (int x = 1; x <= 10000; x++) {
        if ((a * x) % m == 1) {
            cout << x << "\n";
            break; 
        }
    }

    return 0;
}