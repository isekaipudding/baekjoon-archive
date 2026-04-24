// 2549(루빅의 사각형) 문제 : https://www.acmicpc.net/problem/2549
// 알고리즘 태그 목록
/*
그래프 이론
그래프 탐색
백트래킹
중간에서 만나기
양방향 탐색
*/
#include <bits/stdc++.h>

using namespace std;

int board[4][4];
int target_board[4][4];
int min_distance = 8;

int path_type[10];
int path_index[10];
int path_count[10];

int best_type[10];
int best_index[10];
int best_count[10];

void rotateRow(int row) {
    int temp = board[row][3];
    for (int j = 3; j > 0; --j) board[row][j] = board[row][j - 1];
    board[row][0] = temp;
}

void rotateCol(int col) {
    int temp = board[3][col];
    for (int i = 3; i > 0; --i) board[i][col] = board[i - 1][col];
    board[0][col] = temp;
}

int get_mismatch() {
    int mismatch = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] != target_board[i][j]) mismatch++;
        }
    }
    return mismatch;
}

int dfs(int depth, int r_start, int c_start) {
    int mismatch = get_mismatch();

    if (min_distance <= depth + (mismatch + 3) / 4) return 0;

    if (mismatch == 0) {
        min_distance = depth;
        for (int i = 0; i < depth; ++i) {
            best_type[i] = path_type[i];
            best_index[i] = path_index[i];
            best_count[i] = path_count[i];
        }
        return 1;
    }

    int found = 0;

    for (int i = r_start; i < 4; ++i) {
        for (int j = 1; j <= 3; ++j) {
            rotateRow(i);
            path_type[depth] = 1;
            path_index[depth] = i + 1;
            path_count[depth] = j;
            if (dfs(depth + 1, i + 1, 0)) found = 1;
        }
        rotateRow(i);
    }

    for (int i = c_start; i < 4; ++i) {
        for (int j = 1; j <= 3; ++j) {
            rotateCol(i);
            path_type[depth] = 2;
            path_index[depth] = i + 1;
            path_count[depth] = j;
            if (dfs(depth + 1, 0, i + 1)) found = 1;
        }
        rotateCol(i);
    }

    return found;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int value = 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> board[i][j];
            target_board[i][j] = value++;
        }
    }

    dfs(0, 0, 0);

    cout << min_distance << "\n";
    for (int i = 0; i < min_distance; ++i) {
        cout << best_type[i] << " " << best_index[i] << " " << best_count[i] << "\n";
    }

    return 0;
}