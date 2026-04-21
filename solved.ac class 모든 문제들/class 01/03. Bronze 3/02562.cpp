// 2562(최댓값) 문제 : https://www.acmicpc.net/problem/2562
// 알고리즘 태그 목록
/*
구현
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a[9];

    for(int i = 0; i < 9; i++) cin >> a[i];

    int result = 0;
    int temp = 0;

    for(int i = 0; i < 9; i++) {
        if(a[i] > temp) {
            temp = a[i];
            result = i + 1;
        }
    }

    cout << temp << '\n' << result;

    return 0;
}