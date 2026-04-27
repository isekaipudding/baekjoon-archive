// 1388(바닥 장식) 문제 : https://www.acmicpc.net/problem/1388
// 알고리즘 태그 목록
/*
구현
그래프 이론
그래프 탐색
격자 그래프
*/
#include <iostream>
#include <vector>

using namespace std;

char grid[51][51];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    int count = 0;

    // 1. 가로 판자 '-' 개수 세기
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '-') {
                // 첫 번째 열이거나, 바로 왼쪽이 '|'인 경우 새로운 가로 판자 시작
                if (j == 0 || grid[i][j - 1] == '|') {
                    count++;
                }
            }
        }
    }

    // 2. 세로 판자 '|' 개수 세기
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            if (grid[i][j] == '|') {
                // 첫 번째 행이거나, 바로 위쪽이 '-'인 경우 새로운 세로 판자 시작
                if (i == 0 || grid[i - 1][j] == '-') {
                    count++;
                }
            }
        }
    }

    cout << count << "\n";

    return 0;
}