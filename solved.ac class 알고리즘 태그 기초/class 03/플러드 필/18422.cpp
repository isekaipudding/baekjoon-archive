// 18422(Emacs) 문제 : https://www.acmicpc.net/problem/18422
// 알고리즘 태그 목록
/*
구현
그래프 이론
그래프 탐색
플러드 필
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N, M;
char grid[105][105];
bool visited[105][105];

// 행(row)과 열(column)의 변화량
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// 연결된 모든 '*'를 방문 처리하는 플러드 필(BFS)
void bfs(int r, int c) {
    queue<pair<int, int>> q;
    q.push({r, c});
    visited[r][c] = true;

    while (!q.empty()) {
        int curr_r = q.front().first;
        int curr_c = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = curr_r + dr[i];
            int nc = curr_c + dc[i];

            // 격자 범위 내 확인
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                // '*'이고 아직 방문하지 않았다면 같은 사각형의 일부
                if (grid[nr][nc] == '*' && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> grid[i][j];
        }
    }

    int rectangle_count = 0;

    // 전체 격자를 순회하며 방문하지 않은 '*' 탐색
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == '*' && !visited[i][j]) {
                // 새로운 사각형 발견! 플러드 필 시작
                bfs(i, j);
                rectangle_count++;
            }
        }
    }

    cout << rectangle_count << "\n";

    return 0;
}