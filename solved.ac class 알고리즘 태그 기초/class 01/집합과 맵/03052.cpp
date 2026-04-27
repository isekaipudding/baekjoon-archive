// 3052(나머지) 문제 : https://www.acmicpc.net/problem/3052
// 알고리즘 태그 목록
/*
수학
사칙연산
집합과 맵
*/
#include <iostream>
 
using namespace std;

// 집합(set)은 정말 쉽게 말하면 (중복 방지 기능이 있는 리스트)라고 보면 됩니다.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool check[42];
    for(int i = 0; i < 42; i++) check[i] = false;

    for(int i = 0; i < 10; i++) {
        int n;
        cin >> n;
        check[n % 42] = true;
    }

    int result = 0;
    for(int i = 0; i < 42; i++) {
        if(check[i]) result++;
    }

    cout << result;

    return 0;
}