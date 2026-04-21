// 10989(수 정렬하기 3) 문제 : https://www.acmicpc.net/problem/10989
// 알고리즘 태그 목록
/*
정렬
*/
#include <bits/stdc++.h>

using namespace std;

int L[10001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        L[a]++;
    }
    
    for (int i = 1; i <= 10000; i++) {
        if (L[i]) {
            for (int j = 0; j < L[i]; j++)
                cout << i << '\n';
        }
    }

    return 0;
}