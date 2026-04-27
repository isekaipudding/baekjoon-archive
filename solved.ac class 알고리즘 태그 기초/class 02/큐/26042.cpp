// 26042(식당 입구 대기 줄) 문제 : https://www.acmicpc.net/problem/26042
// 알고리즘 태그 목록
/*
구현
자료 구조
큐
*/
#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    queue<int> q;
    int max_size = 0;            // 대기 줄의 최대 크기
    int last_student_at_max = 0; // 최대 크기일 때 맨 뒤의 학생 번호

    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;

        if (type == 1) {
            // 학생 한 명이 대기 줄의 맨 뒤에 섬
            int student_id;
            cin >> student_id;
            q.push(student_id);

            // 현재 대기 줄의 크기 확인 및 갱신
            int current_size = q.size();
            if (current_size > max_size) {
                max_size = current_size;
                last_student_at_max = student_id;
            } 
            else if (current_size == max_size) {
                // 대기 줄의 최대 크기가 같다면, 학생 번호가 가장 작은 경우를 선택
                if (student_id < last_student_at_max) {
                    last_student_at_max = student_id;
                }
            }
        } 
        else if (type == 2) {
            // 식사 준비가 되어 맨 앞의 학생이 나감
            if (!q.empty()) {
                q.pop();
            }
        }
    }

    // 결과 출력 : 최대 대기 인원수와 그때의 마지막 학생 번호
    cout << max_size << " " << last_student_at_max << '\n';

    return 0;
}