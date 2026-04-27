// 34705(효구장) 문제 : https://www.acmicpc.net/problem/34705
// 알고리즘 태그 목록
/*
브루트포스 알고리즘
백트래킹
*/
#include <iostream>
#include <vector>

using namespace std;

long long X, Y;
long long a[5];
bool found;

// 백트래킹 함수
void backtracking(int index, long long current_sum) {
    // 이미 조건을 만족하는 조합을 찾았다면 더 이상의 탐색은 무의미 (가지치기)
    if (found) return;

    // 1. 모든 팩에 대한 결정을 마친 경우 (Base Case)
    if (index == 5) {
        if (current_sum >= X && current_sum <= Y) {
            found = true;
        }
        return;
    }

    // 2. 현재 팩을 포함하는 경우
    backtracking(index + 1, current_sum + a[index]);

    // 3. 현재 팩을 포함하지 않는 경우
    backtracking(index + 1, current_sum);
}

void solve() {
    cin >> X >> Y;
    for (int i = 0; i < 5; i++) {
        cin >> a[i];
    }

    found = false;
    
    // 백트래킹 시작 : 0번 인덱스부터, 초기 합계는 0
    backtracking(0, 0);

    if (found) cout << "YES" << "\n";
    else cout << "NO" << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}