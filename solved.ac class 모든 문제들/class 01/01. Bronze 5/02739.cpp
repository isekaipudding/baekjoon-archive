// 2739(구구단) 문제 : https://www.acmicpc.net/problem/2739
// 알고리즘 태그 목록
/*
구현
수학
*/
#include <bits/stdc++.h>
 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    
    for(int i = 1; i <= 9; i++) cout << n << " * " << i << " = " << n * i << '\n';
 
    return 0;
}