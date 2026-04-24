// 22940(선형 연립 방정식) 문제 : https://www.acmicpc.net/problem/22940
// 알고리즘 태그 목록
/*
수학
선형대수학
가우스 소거법
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<double>> matrix(N, vector<double>(N + 1));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= N; ++j) {
            cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        int pivot = i;
        for (int j = i + 1; j < N; ++j) {
            if (abs(matrix[j][i]) > abs(matrix[pivot][i])) {
                pivot = j;
            }
        }
        swap(matrix[i], matrix[pivot]);

        for (int j = i + 1; j < N; ++j) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k <= N; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }

    vector<double> results(N);
    for (int i = N - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < N; ++j) {
            sum += matrix[i][j] * results[j];
        }
        results[i] = (matrix[i][N] - sum) / matrix[i][i];
    }

    for (int i = 0; i < N; ++i) {
        cout << (int)round(results[i]) << (i == N - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}