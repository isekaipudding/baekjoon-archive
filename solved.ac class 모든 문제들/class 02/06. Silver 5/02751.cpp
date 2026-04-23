// 2751(수 정렬하기 2) 문제 : https://www.acmicpc.net/problem/2751
// 알고리즘 태그 목록
/*
정렬
*/
#include <bits/stdc++.h>

using namespace std;

vector<int> L;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    L.resize(n);

    for(int i = 0; i < n; i++) cin >> L[i];

    sort(L.begin(), L.end());

    for(int i = 0; i < n; i++) cout << L[i] << '\n';

    return 0;
}