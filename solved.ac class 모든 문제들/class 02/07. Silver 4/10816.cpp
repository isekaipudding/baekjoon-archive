// 10816(숫자 카드 2) 문제 : https://www.acmicpc.net/problem/10816
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    
    unordered_map<int, int> counts;
    for (int i = 0; i < n; i++) {
        int card;
        cin >> card;
        counts[card]++;
    }

    int m;
    cin >> m;
    while (m--) {
        int target;
        cin >> target;
        cout << counts[target] << " ";
    }

    return 0;
}