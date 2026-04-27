// 8393(합) 문제 : https://www.acmicpc.net/problem/8393
// 알고리즘 태그 목록
/*
수학
구현
*/
#include <iostream>
 
using namespace std;

// 반복문 기초
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int result = 0;

    for(int i = 1; i <= n; i++) {
        result += i;
    }

    /*
    while문으로 구현하면 다음과 같습니다.
    while(n--) {
        result += n;
        n--;
    }
    */

    cout << result;
 
    return 0;
}