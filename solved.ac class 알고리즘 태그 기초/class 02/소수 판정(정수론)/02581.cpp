// 2581(소수) 문제 : https://www.acmicpc.net/problem/2581
// 알고리즘 태그 목록
/*
수학
정수론
소수 판정
*/
#include <iostream>

using namespace std;

// 소수 판정 함수
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true; // 2는 유일한 짝수 소수
    if (n % 2 == 0) return false; // 2를 제외한 짝수 미리 거르기

    // i < n 대신 i * i <= n (즉, 루트 n) 까지만 확인
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    int result = 0; // 범위 내 소수들의 합
    int min_prime = 10001; // 최솟값을 저장하기 위한 변수 (최대 범위 10,000보다 크게 설정)

    // M부터 N까지 순회하며 소수 판정 진행
    for(int i = m; i <= n; i++) {
        if(is_prime(i)) {
            result += i; // 소수 합산
            // 첫 번째로 발견된 소수가 최솟값이 되며, 이후 더 작은 소수는 나올 수 없음(오름차순 순회)
            min_prime = (i < min_prime) ? i : min_prime;
        }
    }

    // 결과 출력
    if(result) {
        // 소수가 하나 이상 존재하는 경우
        cout << result << '\n';
        cout << min_prime << '\n';
    } else {
        // 범위 내에 소수가 없는 경우 -1 출력
        cout << -1 << '\n';
    }

    return 0;
}