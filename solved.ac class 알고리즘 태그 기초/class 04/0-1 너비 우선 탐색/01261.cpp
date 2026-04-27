// 1261(알고스팟) 문제 : https://www.acmicpc.net/problem/1261
// 알고리즘 태그 목록
/*
그래프 이론
그래프 탐색
최단 경로
데이크스트라
격자 그래프
0-1 너비 우선 탐색
*/
#include <iostream>
#include <vector>
#include <deque>
#include <string>

using namespace std;

int M, N; // M : 가로(열), N : 세로(행)
int grid[101][101];
int dist[101][101];

// 방향 벡터 (dr, dc 스타일)
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int bfs() {
    deque<pair<int, int>> dq;
    
    // 거리 배열 초기화
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            dist[i][j] = -1;
        }
    }

    // 시작점 설정
    dq.push_back({0, 0});
    dist[0][0] = 0;

    while (!dq.empty()) {
        int r = dq.front().first;
        int c = dq.front().second;
        dq.pop_front();

        // 목표 지점 도달 시 반환
        if (r == N - 1 && c == M - 1) {
            return dist[r][c];
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M && dist[nr][nc] == -1) {
                if (grid[nr][nc] == 0) {
                    /* [0-1 BFS의 차이점 1] 
                       가중치가 0(빈 방)인 경우, 이전 노드와 가중치가 같으므로
                       탐색 순서를 앞당기기 위해 deque의 앞에 삽입합니다. */
                    dist[nr][nc] = dist[r][c];
                    dq.push_front({nr, nc});
                } else {
                    /* [0-1 BFS의 차이점 2]
                       가중치가 1(벽)인 경우, 비용이 증가하므로 
                       일반적인 BFS처럼 deque의 뒤에 삽입합니다. */
                    dist[nr][nc] = dist[r][c] + 1;
                    dq.push_back({nr, nc});
                }
            }
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // M(가로), N(세로) 입력
    cin >> M >> N;

    for (int i = 0; i < N; ++i) {
        string line;
        cin >> line;
        for (int j = 0; j < M; ++j) {
            grid[i][j] = line[j] - '0';
        }
    }

    cout << bfs() << "\n";

    return 0;
}