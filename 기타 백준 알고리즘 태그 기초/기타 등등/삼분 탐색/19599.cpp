// 19599(이진 삼진 탐색 놀이 1) 문제 : https://www.acmicpc.net/problem/19599
// 알고리즘 태그 목록
/*
이분 탐색
삼분 탐색
*/
#include <bits/stdc++.h>

using namespace std;

int B[500005];
int T[500005];

void compute_binary(int left, int right, int depth) {
    if (left > right) return;

    int mid = (left + right) / 2;
    B[mid] = depth;

    compute_binary(left, mid - 1, depth + 1);
    compute_binary(mid + 1, right, depth + 1);
}

void compute_ternary(int left, int right, int depth) {
    if (left > right) return;

    int lt = left + (right - left) / 3;
    int rt = right - (right - left) / 3;

    T[lt] = depth;

    if (lt == rt) {
        compute_ternary(left, lt - 1, depth + 2);
        compute_ternary(lt + 1, right, depth + 2);
    } else {
        T[rt] = depth + 1;

        compute_ternary(left, lt - 1, depth + 2);
        compute_ternary(lt + 1, rt - 1, depth + 2);
        compute_ternary(rt + 1, right, depth + 2);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    compute_binary(0, N - 1, 0);
    compute_ternary(0, N - 1, 0);

    int less = 0, equal = 0, greater = 0;

    for (int i = 0; i < N; i++) {
        if (B[i] < T[i]) less++;
        else if (B[i] == T[i]) equal++;
        else greater++;
    }

    cout << less << "\n" << equal << "\n" << greater << "\n";

    return 0;
}