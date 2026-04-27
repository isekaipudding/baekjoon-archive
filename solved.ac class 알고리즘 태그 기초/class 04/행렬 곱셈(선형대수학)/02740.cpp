// 2740(행렬 곱셈) 문제 : https://www.acmicpc.net/problem/2740
// 알고리즘 태그 목록
/*
수학
구현
선형대수학
*/
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief 두 행렬의 곱을 계산하여 반환하는 함수
 * @param A N x M 크기의 행렬
 * @param B M x K 크기의 행렬
 * @return N x K 크기의 결과 행렬
 */
vector<vector<int>> matrix_product(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int N = A.size();
    int M = A[0].size();
    int K = B[0].size();

    // 결과를 저장할 N x K 크기의 행렬을 0으로 초기화
    vector<vector<int>> C(N, vector<int>(K, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            for (int l = 0; l < M; l++) {
                C[i][j] += A[i][l] * B[l][j];
            }
        }
    }
    return C;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;

    // 행렬 A 입력
    cin >> N >> M;
    vector<vector<int>> A(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> A[i][j];
        }
    }

    // 행렬 B 입력
    cin >> M >> K;
    vector<vector<int>> B(M, vector<int>(K));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            cin >> B[i][j];
        }
    }

    // 함수 호출을 통한 행렬 곱셈 수행
    vector<vector<int>> result = matrix_product(A, B);

    // 결과 출력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            cout << result[i][j] << (j == K - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}