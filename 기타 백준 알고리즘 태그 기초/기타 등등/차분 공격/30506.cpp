// 30506(가위 가위 가위) 문제 : https://www.acmicpc.net/problem/30506
// 알고리즘 태그 목록
/*
차분 공격
*/
#include <bits/stdc++.h>

using namespace std;

// 이 문제는 인터랙티브 문제입니다.

int main() {
    // 인터랙티브 문제에서는 cin.tie(nullptr)를 쓰면 
    // 버퍼가 꼬일 수 있으므로 사용하지 않는 것이 안전합니다.
    ios::sync_with_stdio(false);

    int K;
    cin >> K; // 초기 상태 (모두 가위일 때의 승수)

    string machine_hand = "";

    // 100자리의 손 모양을 하나씩 알아냅니다.
    for (int i = 0; i < 100; i++) {
        string query(100, '2'); // 100자리 모두 가위(2)로 초기화
        query[i] = '0';         // i번째만 바위(0)로 변경 (차분 생성)

        // 질문 출력 (endl은 자동으로 flush를 수행합니다)
        cout << "? " << query << endl;

        int K_prime;
        cin >> K_prime; // 변경 후의 승수 입력

        int diff = K_prime - K;

        if (diff == 0) {
            machine_hand += "0"; // 변화 없음 -> 머신은 바위(0)
        } else if (diff == 1) {
            machine_hand += "2"; // 승리 추가 -> 머신은 가위(2)
        } else if (diff == -1) {
            machine_hand += "5"; // 승리 박탈 -> 머신은 보(5)
        }
    }

    // 최종 정답 출력
    cout << "! " << machine_hand << endl;

    return 0;
}