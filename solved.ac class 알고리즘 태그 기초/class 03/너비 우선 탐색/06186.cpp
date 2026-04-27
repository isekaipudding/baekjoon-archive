// 6186(Best Grass) 문제 : https://www.acmicpc.net/problem/6186
// 알고리즘 태그 목록
/*
구현
그래프 이론
그래프 탐색
너비 우선 탐색
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int R, C;
char grid[101][101];
bool visited[101][101];

// 상, 하, 좌, 우 순서
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// 초보자도 이해하기 쉬운 BFS 함수
void bfs(int r, int c) {
    queue<pair<int, int>> q;
    
    // 시작점 큐에 삽입 및 방문 처리
    q.push({r, c});
    visited[r][c] = true;

    while (!q.empty()) {
        // 최근 좌표를 추출합니다.
        int current_r = q.front().first;
        int current_c = q.front().second;
        q.pop();

        // 인접한 4방향 확인
        for (int i = 0; i < 4; ++i) {
            // 차례대로 다음 행(nr), 다음 열(nc) 계산
            int nr = current_r + dr[i];
            int nc = current_c + dc[i];

            // 1. 농장 범위 내에 있고
            // 2. 풀('#')이 존재하며
            // 3. 아직 방문하지 않은 경우
            if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                // 풀('#')이 있고 아직 방문하지 않았다면 탐색 계속
                if (grid[nr][nc] == '#' && !visited[nr][nc]) {
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

    // 행(R)과 열(C) 입력
    cin >> R >> C;

    // 농장 상태 입력
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> grid[i][j];
        }
    }

    int clump_count = 0;

    // 전체 농장을 순회하며 새로운 풀 덩어리 탐색
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            // 풀을 발견하면 BFS로 연결된 모든 부위를 방문 처리
            if (grid[i][j] == '#' && !visited[i][j]) {
                bfs(i, j);
                clump_count++;
            }
        }
    }

    cout << clump_count << "\n";

    return 0;
}