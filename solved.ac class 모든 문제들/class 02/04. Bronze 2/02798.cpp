// 2798(벌집) 문제 : https://www.acmicpc.net/problem/2798
// 알고리즘 태그 목록
/*
브루트포스 알고리즘
*/
#include <bits/stdc++.h>

using namespace std;

vector<int> numbers;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    numbers.resize(n);

    for(int i = 0; i < n; i++) cin >> numbers[i];

    sort(numbers.begin(), numbers.end());

    int MAX = 0;
    for(int i = 0; i < n-2; i++) {
        if (MAX == m) break;
        for(int j = i+1; j < n-1; j++) {
            for(int k = j+1; k < n; k++) {
                if(numbers[i] + numbers[j] + numbers[k] <= m) {
                    MAX = max(MAX, numbers[i] + numbers[j] + numbers[k]);
                }
                else break;
            }
        }
    }

    cout << MAX;

    return 0;
}