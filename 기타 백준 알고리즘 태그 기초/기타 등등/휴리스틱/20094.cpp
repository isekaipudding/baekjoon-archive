// 20094(Sudoku 1) 문제 : https://www.acmicpc.net/problem/20094
// 알고리즘 태그 목록
/*
구현
해 구성하기
휴리스틱
*/
#include <bits/stdc++.h>

using namespace std;

int n = 2;
int N = n * n;
int board[4][4];

bool is_safe(int r, int c, int num) {
    for (int i = 0; i < N; i++) {
        if (board[r][i] == num || board[i][c] == num) return false;
    }
    int startRow = r - r % n;
    int startCol = c - c % n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i + startRow][j + startCol] == num) return false;
        }
    }
    return true;
}

bool find_best_cell(int &row, int &col) {
    int min_options = N + 1;
    row = -1; col = -1;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (board[r][c] == 0) {
                int options = 0;
                for (int num = 1; num <= N; num++) {
                    if (is_safe(r, c, num)) options++;
                }
                
                if (options < min_options) {
                    min_options = options;
                    row = r;
                    col = c;
                }
            }
        }
    }
    return row != -1;
}

bool solve() {
    int r, c;
    if (!find_best_cell(r, c)) return true;

    for (int num = 1; num <= N; num++) {
        if (is_safe(r, c, num)) {
            board[r][c] = num;
            if (solve()) return true;
            board[r][c] = 0;
        }
    }
    return false;
}

int main() {
    int input_data[4][4] = {
        {0, 2, 4, 0},
        {1, 0, 0, 3},
        {4, 0, 0, 2},
        {0, 1, 3, 0}
    };

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            board[i][j] = input_data[i][j];

    if (solve()) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << board[i][j] << (j == N - 1 ? "" : " ");
            }
            cout << endl;
        }
    } else {
        cout << "해를 찾을 수 없습니다." << endl;
    }

    return 0;
}