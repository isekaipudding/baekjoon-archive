// 2108(통계학) 문제 : https://www.acmicpc.net/problem/2108
// 알고리즘 태그 목록
/*
수학
구현
정렬
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> v(n);
    vector<int> freq(8001, 0);
    double sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> v[i];
        sum += v[i];
        freq[v[i] + 4000]++;
    }

    sort(v.begin(), v.end());

    int mean = round(sum / n);
    cout << mean << "\n";
    cout << v[n / 2] << "\n";

    int max_freq = 0;
    for (int i = 0; i <= 8000; i++) {
        if (freq[i] > max_freq) max_freq = freq[i];
    }

    vector<int> modes;
    for (int i = 0; i <= 8000; i++) {
        if (freq[i] == max_freq) {
            modes.push_back(i - 4000);
        }
    }

    if (modes.size() > 1) {
        cout << modes[1] << "\n";
    } else {
        cout << modes[0] << "\n";
    }

    cout << v.back() - v.front() << "\n";

    return 0;
}