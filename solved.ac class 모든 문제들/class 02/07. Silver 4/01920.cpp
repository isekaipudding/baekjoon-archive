// 1920(수 찾기) 문제 : https://www.acmicpc.net/problem/1920
// 알고리즘 태그 목록
/*
자료 구조
정렬
이분 탐색
집합과 맵
해시를 사용한 집합과 맵
*/
#include <bits/stdc++.h>

using namespace std;

bool binary_search(const vector<int>& array, int target) {
    int low = 0;
    int high = array.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (array[mid] == target) return true;
        else if (array[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    int m;
    cin >> m;
    while (m--) {
        int target;
        cin >> target;
        if (binary_search(a, target)) cout << "1\n";
        else cout << "0\n";
    }

    return 0;
}