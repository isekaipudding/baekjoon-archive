// 11651(좌표 정렬하기 2) 문제 : https://www.acmicpc.net/problem/11651
// 알고리즘 태그 목록
/*
정렬
*/
#include <bits/stdc++.h>

using namespace std;

bool compare(const pair<int, int> &a, const pair<int, int> &b) {
    if (a.second != b.second) {
        return a.second < b.second;
    }
    return a.first < b.first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> points(n);

    for(int i = 0; i < n; i++) 
        cin >> points[i].first >> points[i].second;

    sort(points.begin(), points.end(), compare);

    for(int i = 0; i < n; i++)
        cout << points[i].first << " " << points[i].second << "\n";

    return 0;
}