// 35152(주니어 개발자 동우의 직행 취업일기) 문제 : https://www.acmicpc.net/problem/35152
// 알고리즘 태그 목록
/*
트리
해 구성하기
트리의 지름
*/
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll x = 1;
    ll y = N;
    for(ll i = 1; i * i <= N; i++) {
        if(N % i == 0) {
            x = i;
            y = N / i;
        }
    }

    ll V = x + y + 2;
    cout << V << "\n";
    cout << "1 2" << "\n";

    for(ll i = 0; i < x; i++) {
        cout << 1 << " " << 3 + i << "\n";
    }

    for(ll i = 0; i < y; i++) {
        cout << 2 << " " << x + 3 + i << "\n";
    }

    return 0;
}