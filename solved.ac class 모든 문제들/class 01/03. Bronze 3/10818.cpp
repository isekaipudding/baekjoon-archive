// 10818(최소, 최대) 문제 : https://www.acmicpc.net/problem/10818
// 알고리즘 태그 목록
/*
수학
구현
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int max_value = -1000000;
    int min_value = 1000000;

    while(n--) {
        int a;
        cin >> a;

        if(a > max_value) max_value = a;
        if(a < min_value) min_value = a;
    }

    cout << min_value << " " << max_value;

    return 0;
}