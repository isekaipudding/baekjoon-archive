// 10773(제로) 문제 : https://www.acmicpc.net/problem/10773
// 알고리즘 태그 목록
/*
구현
자료 구조
스택
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    vector<int> v;
    while(k--) {
        int n;
        cin >> n;

        if (n == 0) {
            if (!v.empty()) v.pop_back();
        } else {
            v.push_back(n);
        }
    }

    long long total_sum = 0;
    for (int num : v) total_sum += num;

    cout << total_sum << "\n";

    return 0;
}