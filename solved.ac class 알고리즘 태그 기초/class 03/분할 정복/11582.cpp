// 11582(치킨 TOP N) 문제 : https://www.acmicpc.net/problem/11582
// 알고리즘 태그 목록
/*
정렬
분할 정복
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> scores(n);
    for (int i = 0; i < n; ++i) {
        cin >> scores[i];
    }

    int k;
    cin >> k;

    // k명이 남아있을 때 한 그룹이 담당하는 치킨집의 수
    int group_size = n / k;

    // 배열을 group_size 단위로 쪼개어 각 구간만 정렬
    // 구간 별로 나누어서 부분 문제들(여기서는 정렬)을 해결하면 전체 문제가 해결됩니다.(분할 정복)
    for (int i = 0; i < n; i += group_size) {
        // scores.begin() + i부터 scores.begin() + i + group_size 직전까지 정렬
        sort(scores.begin() + i, scores.begin() + i + group_size);
    }

    // 결과 출력
    for (int i = 0; i < n; ++i) {
        cout << scores[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}