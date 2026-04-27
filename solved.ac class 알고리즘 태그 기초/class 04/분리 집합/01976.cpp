// 1976(여행 가자) 문제 : https://www.acmicpc.net/problem/1976
// 알고리즘 태그 목록
/*
자료 구조
그래프 이론
그래프 탐색
분리 집합
*/
#include <iostream>
#include <vector>

using namespace std;

int N, M;
int parent[201];

// 원소 x의 루트 노드를 찾습니다. (경로 압축 적용)
int find_parent(int x) {
    if (parent[x] == x) return x;
    // 경로 압축 : 부모를 루트로 직접 연결하여 향후 탐색 속도를 높임
    return parent[x] = find_parent(parent[x]);
}

// 두 원소 a와 b가 속한 집합을 합칩니다.
void union_parent(int a, int b) {
    a = find_parent(a);
    b = find_parent(b);

    // 더 작은 번호의 노드를 부모로 삼도록 규칙 설정
    if (a < b) parent[b] = a;
    else if (a > b) parent[a] = b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    // 1. 부모 테이블 자기 자신으로 초기화
    for (int i = 1; i <= N; ++i) {
        parent[i] = i;
    }

    // 2. 인접 행렬 정보를 바탕으로 Union 연산 수행
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            int connected;
            cin >> connected;
            if (connected == 1) {
                union_parent(i, j);
            }
        }
    }

    // 3. 여행 계획 확인
    int start_city;
    cin >> start_city;
    int root = find_parent(start_city);
    
    bool possible = true;
    for (int i = 1; i < M; ++i) {
        int next_city;
        cin >> next_city;
        // 여행 계획에 포함된 모든 도시의 루트가 동일해야 연결된 것임
        if (root != find_parent(next_city)) {
            possible = false;
            break;
        }
    }

    if (possible) cout << "YES" << "\n";
    else cout << "NO" << "\n";

    return 0;
}