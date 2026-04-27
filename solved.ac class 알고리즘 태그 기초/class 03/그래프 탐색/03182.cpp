// 3182(한동이는 공부가 하기 싫어!) 문제 : https://www.acmicpc.net/problem/3182
// 알고리즘 태그 목록
/*
그래프 이론
브루트포스 알고리즘
그래프 탐색
*/
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int graph[1001];
bool visited[1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 각 학생이 지목한 번호 입력 (1번부터 n번까지)
    for (int i = 1; i <= n; i++) {
        cin >> graph[i];
    }

    int max_count = -1;
    int result = 0;

    // 모든 정점을 시작점으로 하여 탐색 (브루트포스)
    for (int i = 1; i <= n; i++) {
        // 방문 배열 초기화
        memset(visited, false, sizeof(visited));
        
        int current = i;
        int count = 0;

        // 이미 만난 사람을 다시 만날 때까지 전진
        while (!visited[current]) {
            visited[current] = true;
            current = graph[current];
            count++;
        }

        // 최대 방문 횟수 갱신 (작은 번호부터 순회하므로 '>' 사용 시 자동 최솟값 유지)
        if (count > max_count) {
            max_count = count;
            result = i;
        }
    }

    cout << result << "\n";

    return 0;
}