// 10871(X보다 작은 수) 문제 : https://www.acmicpc.net/problem/10871
// 알고리즘 태그 목록
/*
구현
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    int a[n];

    for(int i = 0; i < n; i++) cin >> a[i];

    for(int i = 0; i < n; i++) {
        if(a[i] < x) cout << a[i] << ' ';
    }

    return 0;
}