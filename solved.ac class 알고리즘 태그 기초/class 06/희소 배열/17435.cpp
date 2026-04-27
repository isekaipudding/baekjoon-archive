// 17435(합성함수와 쿼리) 문제 : https://www.acmicpc.net/problem/17435
// 알고리즘 태그 목록
/*
자료 구조
희소 배열
*/
#include <iostream>
#include <vector>

using namespace std;

// m의 최대 200,000, n의 최대 500,000
const int MAX_M = 200001;
const int MAX_K = 20; // 2^19 > 500,000

// sparse[k][i]: i에서 2^k번 이동했을 때의 위치
int sparse[MAX_K][MAX_M];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;

    // f^1(x) 즉, 2^0번 이동한 결과 입력 (기초값)
    for (int i = 1; i <= m; i++) {
        cin >> sparse[0][i];
    }

    // 1. 희소 배열 전처리 (Pre-computation)
    // k=1 (2^1번 이동)부터 k=19 (2^19번 이동)까지 채우기
    for (int k = 1; k < MAX_K; k++) {
        for (int i = 1; i <= m; i++) {
            // 2^k 이동 = 2^(k-1) 이동 후 다시 2^(k-1) 이동
            int intermediate = sparse[k - 1][i];
            sparse[k][i] = sparse[k - 1][intermediate];
        }
    }

    int Q;
    cin >> Q;

    // 2. 쿼리 처리
    while (Q--) {
        int n, x;
        cin >> n >> x;

        // n을 이진수로 분해하여 점프하기
        for (int k = MAX_K - 1; k >= 0; k--) {
            // n의 k번째 비트가 켜져 있다면 2^k만큼 점프
            if (n & (1 << k)) {
                x = sparse[k][x];
            }
        }
        cout << x << "\n";
    }

    return 0;
}