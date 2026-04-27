// 7562(나이트의 이동) 문제 : https://www.acmicpc.net/problem/7562
// 알고리즘 태그 목록
/*
그래프 이론
그래프 탐색
너비 우선 탐색
최단 경로
격자 그래프
*/
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int L;
int start_r, start_c, end_r, end_c;
int dist[301][301];

// 나이트가 이동할 수 있는 8가지 방향 (dr, dc)
int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

int bfs() {
    // 매 테스트 케이스마다 거리 배열 초기화 (-1은 미방문)
    memset(dist, -1, sizeof(dist));

    queue<pair<int, int>> q;
    
    // 시작점 설정
    q.push({start_r, start_c});
    dist[start_r][start_c] = 0;

    while (!q.empty()) {
        int curr_r = q.front().first;
        int curr_c = q.front().second;
        q.pop();

        // 목표 지점에 도달하면 현재 거리 반환
        // curr는 current의 줄임말입니다.
        if (curr_r == end_r && curr_c == end_c) {
            return dist[curr_r][curr_c];
        }

        for (int i = 0; i < 8; ++i) {
            int nr = curr_r + dr[i];
            int nc = curr_c + dc[i];

            // 1. 체스판 범위를 벗어나지 않고
            // 2. 아직 방문하지 않은 칸인 경우
            if (nr >= 0 && nr < L && nc >= 0 && nc < L) {
                if (dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[curr_r][curr_c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }
    return 0; // 시작점과 끝점이 같은 경우 등
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        cin >> L;
        // 0-based index입니다.
        cin >> start_r >> start_c;
        cin >> end_r >> end_c;

        cout << bfs() << "\n";
    }

    return 0;
}