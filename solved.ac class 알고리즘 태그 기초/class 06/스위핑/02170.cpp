// 2170(선 긋기) 문제 : https://www.acmicpc.net/problem/2170
// 알고리즘 태그 목록
/*
정렬
스위핑
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 선분의 시작점과 끝점을 저장할 구조체 (std::pair로 대체 가능)
struct Line {
    int start, end;
};

// 정렬 기준: 시작점 기준 오름차순
bool compare(const Line& a, const Line& b) {
    if (a.start == b.start) return a.end < b.end;
    return a.start < b.start;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Line> lines(N);
    for (int i = 0; i < N; i++) {
        cin >> lines[i].start >> lines[i].end;
    }

    // 1. 시작점 기준으로 정렬 (O(N log N))
    sort(lines.begin(), lines.end(), compare);

    // 2. 스위핑을 통한 길이 계산
    long long total_length = 0;
    int current_start = lines[0].start;
    int current_end = lines[0].end;

    for (int i = 1; i < N; i++) {
        // 다음 선분이 현재 선분과 겹치거나 이어지는 경우
        if (lines[i].start <= current_end) {
            current_end = max(current_end, lines[i].end);
        }
        // 아예 새로운 선분이 나타난 경우
        else {
            total_length += (current_end - current_start);
            current_start = lines[i].start;
            current_end = lines[i].end;
        }
    }

    // 마지막으로 남아있는 선분의 길이를 더해줌
    total_length += (current_end - current_start);

    cout << total_length << "\n";

    return 0;
}