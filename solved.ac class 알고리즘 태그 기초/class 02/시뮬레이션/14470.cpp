// 14470(전자레인지) 문제 : https://www.acmicpc.net/problem/14470
// 알고리즘 태그 목록
/*
수학
구현
사칙연산
시뮬레이션
*/
#include <iostream>

using namespace std;

// 시뮬레이션은 현실의 상황을 얼마나 꼼꼼하게 읽고 예외 없이 구현하는 알고리즘입니다.
// 말이야 알고리즘이지 그냥 말 그대로 시뮬레이션 돌리기 위해 구현한다고 보면 됩니다.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c, d, e;
    // 하나씩 입력받는 사용자 스타일 준수
    cin >> a; // 현재 온도
    cin >> b; // 목표 온도
    cin >> c; // 얼어있을 때 1도 올리는 데 걸리는 시간
    cin >> d; // 해동하는 데 걸리는 시간
    cin >> e; // 다 녹았을 때 1도 올리는 데 걸리는 시간

    int total_time = 0;

    // 시뮬레이션 : 현재 온도(a)가 목표 온도(b)가 될 때까지 과정을 나눔
    if (a < 0) {
        // 1단계 : 0도까지 가열 (얼어있는 상태)
        total_time += (-a) * c;
        // 2단계 : 0도에서 해동
        total_time += d;
        // 3단계 : 0도에서 목표 온도(b)까지 가열
        total_time += b * e;
    } else {
        // 이미 0도보다 높은 경우 : 목표 온도(b)까지 차이만큼 가열
        total_time += (b - a) * e;
    }

    // 결과 출력
    cout << total_time << '\n';

    return 0;
}