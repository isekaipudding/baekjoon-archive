// 1018(체스판 다시 칠하기) 문제 : https://www.acmicpc.net/problem/1018
// 알고리즘 태그 목록
/*
구현
브루트포스 알고리즘
*/
#include <bits/stdc++.h>

using namespace std;

int count_repaint(int r, int c, const vector<string>& board) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char expected = ((i + j) % 2 == 0) ? 'W' : 'B';
            if (board[r + i][c + j] != expected) {
                count++;
            }
        }
    }
    return min(count, 64 - count);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int row, col;
    cin >> row >> col;

    vector<string> graph(row);

    for(int i = 0; i < row; i++) cin >> graph[i];

    int result = 64;

    for(int i = 0; i <= row - 8; i++) {
        for(int j = 0; j <= col - 8; j++) {
            result = min(result, count_repaint(i, j, graph));
        }
    }

    cout << result;

    return 0;
}