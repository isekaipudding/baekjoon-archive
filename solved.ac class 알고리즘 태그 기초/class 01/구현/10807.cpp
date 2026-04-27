// 10807(개수 세기) 문제 : https://www.acmicpc.net/problem/10807
// 알고리즘 태그 목록
/*
구현
*/
#include <iostream>
 
using namespace std;

// 배열 기초
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int a[n];

    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] = x;
    }

    int v;
    cin >> v;

    int result = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] == v) result++;
    }

    cout << result;
 
    return 0;
}