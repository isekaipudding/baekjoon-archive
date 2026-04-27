// 1934(최소공배수) 문제 : https://www.acmicpc.net/problem/1934
// 알고리즘 태그 목록
/*
수학
정수론
유클리드 호제법
*/
#include <iostream>
#include <algorithm>

using namespace std;

// 가독성을 위한 타입 별칭 설정
using ll = long long;

// 최대 공약수 함수(유클리드 호제법)
int gcd(int a, int b) {
    // a가 b보다 작으면 순서를 바꾸어 가독성과 일관성 유지
    if (a < b) swap(a, b);

    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// 최소공배수 함수
ll lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    
    // 오버플로우 방지
    return (ll)(a / gcd(a, b)) * b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int a, b;
        cin >> a >> b;

        // 최종 결과 출력
        cout << lcm(a, b) << '\n';
    }

    return 0;
}