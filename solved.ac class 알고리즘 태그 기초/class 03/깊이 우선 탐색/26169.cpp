// 26169(세 번 이내에 사과를 먹자) 문제 : https://www.acmicpc.net/problem/26169
// 알고리즘 태그 목록
/*
그래프 이론
그래프 탐색
깊이 우선 탐색
백트래킹
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int board[5][5];
// 행(row)과 열(column)의 변화량을 나타내는 dr, dc
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

bool found = false;

// r : 현재 행, c : 현재 열, depth : 이동 횟수, apples : 먹은 사과 수
void dfs(int r, int c, int depth, int apples) {
    // 사과가 있는 칸(1)이면 사과 개수 추가
    if (board[r][c] == 1) apples++;

    // 사과를 2개 이상 먹었다면 성공
    if (apples >= 2) {
        found = true;
        return;
    }

    // 3번 이동했는데도 사과를 못 채웠다면 해당 경로는 종료
    if (depth == 3) return;

    // 현재 칸을 장애물로 임시 변경 (지나온 길 표시)
    int temp = board[r][c];
    board[r][c] = -1;

    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        // 격자 범위 내에 있고 장애물(-1)이 아닌 경우만 이동
        if (nr >= 0 && nr < 5 && nc >= 0 && nc < 5 && board[nr][nc] != -1) {
            dfs(nr, nc, depth + 1, apples);
            if (found) return; // 이미 찾았다면 더 이상의 탐색은 불필요
        }
    }

    // 탐색이 끝난 후 원래 상태로 복구 (Backtracking)
    board[r][c] = temp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 5x5 보드 정보 입력
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> board[i][j];
        }
    }

    int start_r, start_c;
    cin >> start_r >> start_c;

    // DFS 시작 (깊이 0, 사과 0개부터 시작)
    dfs(start_r, start_c, 0, 0);

    if (found) cout << 1 << "\n";
    else cout << 0 << "\n";

    return 0;
}