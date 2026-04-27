// 27160(할리갈리) 문제 : https://www.acmicpc.net/problem/27160
// 알고리즘 태그 목록
/*
구현
자료 구조
문자열
집합과 맵
해시를 사용한 집합과 맵
*/
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 과일 이름을 Key로, 개수를 Value로 저장하는 해시 맵
    // 정렬이 필요 없으므로 탐색 효율이 O(1)인 unordered_map 사용
    unordered_map<string, int> fruits;

    // 카드 정보 입력 및 과일별 개수 합산
    for (int i = 0; i < n; i++) {
        string name;
        int count;
        cin >> name;
        cin >> count;

        fruits[name] += count;
    }

    // 종을 쳐야 하는지 확인 (어떤 과일이든 합계가 정확히 5인 경우)
    bool ring_bell = false;

    // 해시 맵의 모든 요소를 순회하며 조건 확인
    // auto&를 사용하여 맵의 (Key, Value) 쌍에 접근
    for (auto& pair : fruits) {
        if (pair.second == 5) {
            ring_bell = true;
            break;
        }
    }

    // 결과 출력
    if (ring_bell) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }

    return 0;
}