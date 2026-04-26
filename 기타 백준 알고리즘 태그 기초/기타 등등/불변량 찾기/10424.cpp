// 10424(알고리즘 기말고사) 문제 : https://www.acmicpc.net/problem/10424
// 알고리즘 태그 목록
/*
구현
정렬
불변량 찾기
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> final_ranks(n + 1);

    for (int rank = 1; rank <= n; ++rank) {
        int student_id;
        cin >> student_id;
        final_ranks[student_id] = rank;
    }

    for (int i = 1; i <= n; ++i) {
        cout << i - final_ranks[i] << "\n";
    }

    return 0;
}