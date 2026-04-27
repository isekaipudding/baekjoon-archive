// 12867(N차원 여행) 문제 : https://www.acmicpc.net/problem/12867
// 알고리즘 태그 목록
/*
자료 구조
집합과 맵
해시를 사용한 집합과 맵
값 / 좌표 압축
*/
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> target_dimentions(m);
    for (int i = 0; i < m; ++i) {
        cin >> target_dimentions[i];
    }

    string directions;
    cin >> directions;

    /* [초보자를 위한 핵심 주석 : 왜 좌표 압축인가?]
       n이 10억이므로 전체 좌표를 배열로 만들 수 없습니다.
       대신 '값이 0이 아닌 차원'만 map에 저장합니다.
       이것은 10억 개의 차원 중 의미 있는(값이 변한) 소수의 좌표만 
       따로 추출하여 관리하는 '좌표 압축'의 원리와 같습니다.
    */
    map<int, int> current_position;
    set<map<int, int>> visited;

    // 시작 지점 (0, 0, ..., 0)을 방문 기록에 추가
    // 빈 map은 모든 차원의 값이 0임을 의미합니다.
    visited.insert(current_position);

    for (int i = 0; i < m; ++i) {
        int dimention = target_dimentions[i];
        int direction = (directions[i] == '+' ? 1 : -1);

        // 해당 차원의 좌표 변경
        current_position[dimention] += direction;

        // 좌표가 0이 되면 map에서 제거하여 '표준 상태' 유지
        // (0, 0, 1)과 (0, 0, 1, 0, 0)이 같은 상태임을 보장하기 위함입니다.
        if (current_position[dimention] == 0) {
            current_position.erase(dimention);
        }

        // 이미 방문한 적이 있는 좌표 세트인지 확인
        if (visited.count(current_position)) {
            cout << 0 << "\n";
            return 0;
        }

        // 새로운 좌표 상태를 방문 기록에 추가
        visited.insert(current_position);
    }

    // 모든 이동 후에도 중복 방문이 없다면 1 출력
    cout << 1 << "\n";

    return 0;
}