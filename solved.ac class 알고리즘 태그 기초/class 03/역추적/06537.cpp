// 6537(In Danger) 문제 : https://www.acmicpc.net/problem/6537
// 알고리즘 태그 목록
/*
수학
역추적
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    while (cin >> s && s != "00e0") {
        // 1. 입력 파싱 (XYeZ -> n)
        int x = s[0] - '0';
        int y = s[1] - '0';
        int z = s[3] - '0';

        int n = (x * 10 + y);
        for (int i = 0; i < z; ++i) {
            n *= 10;
        }

        /* 2. 요세푸스 문제 해결 (n = 2^m + l 형태 찾기)
           가장 큰 2의 거듭제곱(2^m)을 찾아 n에서 뺀 값을 l이라 하면,
           생존자의 위치는 2*l + 1 입니다.
        */
        int m = 1;
        while (m <= n) {
            m <<= 1; // 2의 거듭제곱을 키워나감
        }
        m >>= 1; // n보다 작거나 같은 가장 큰 2^m

        int l = n - m;
        int result = 2 * l + 1;

        cout << result << "\n";
    }

    return 0;
}