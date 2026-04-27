// 11502(세 개의 소수 문제) 문제 : https://www.acmicpc.net/problem/11502
// 알고리즘 태그 목록
/*
수학
브루트포스 알고리즘
정수론
소수 판정
에라토스테네스의 체
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 소수 판정 함수
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) { // 효율을 위해 i*i까지 확인
        if (n % i == 0) return false;
    }
    return true;
}

// 아아... 이것은 『에라토스테네스의 체』라고 한다. 소수를 미리 다 구해버리지.
bool is_prime_table[1001];
vector<int> primes;

void sieve() {
    fill(is_prime_table, is_prime_table + 1001, true);
    is_prime_table[0] = is_prime_table[1] = false;
    for (int i = 2; i * i <= 1000; i++) {
        if (is_prime_table[i]) {
            for (int j = i * i; j <= 1000; j += i) {
                is_prime_table[j] = false;
            }
        }
    }
    // 소수만 따로 리스트업
    for (int i = 2; i <= 1000; i++) {
        if (is_prime_table[i]) {
            primes.push_back(i);
        }
    }
}

int main() {
    // 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1. 소수 데이터 미리 생성 (Pre-computation)
    sieve();

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> result;
        // 골드바흐의 약한 추측 응용: 홀수는 3을 빼서 짝수로, 짝수는 2를 빼서 짝수로 만듦
        if (n % 2 == 0) {
            result.push_back(2);
            n -= 2;
        } else {
            result.push_back(3);
            n -= 3;
        }

        // 2. 남은 수(짝수)를 두 소수의 합으로 분해 (골드바흐의 강한 추측 형태)
        bool found = false;
        for (int i = 0; i < primes.size(); i++) {
            int p1 = primes[i];
            if (p1 > n) break;

            int p2 = n - p1;
            // 에라토스테네스의 체 결과와 직접 정의한 소수 판정 함수를 모두 활용
            if (p2 >= 2 && is_prime_table[p2] && is_prime(p2)) {
                result.push_back(p1);
                result.push_back(p2);
                found = true;
                break;
            }
        }

        // 3. 결과 출력
        if (found) {
            sort(result.begin(), result.end());
            for (int i = 0; i < 3; i++) {
                cout << result[i] << (i == 2 ? "" : " ");
            }
            cout << '\n';
        } else {
            cout << 0 << '\n'; // 실제로는 발생하지 않음 (7 이상의 홀수는 항상 성립)
        }
    }

    return 0;
}