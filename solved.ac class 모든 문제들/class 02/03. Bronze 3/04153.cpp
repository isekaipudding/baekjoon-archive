// 4153(직각삼각형) 문제 : https://www.acmicpc.net/problem/4153
// 알고리즘 태그 목록
/*
수학
기하학
피타고라스 정리
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, y, z;
    while (cin >> x >> y >> z) {
        if(x == 0 && y == 0 && z == 0) break;

        if (x > y) swap(x, y);
        if (y > z) swap(y, z);
        if (x > y) swap(x, y);

        if (x * x + y * y == z * z) cout << "right" << '\n';
        else cout << "wrong" << '\n';
    }

    return 0;
}