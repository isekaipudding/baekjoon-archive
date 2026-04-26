// 15353(큰 수 A+B (2)) 문제 : https://www.acmicpc.net/problem/15353
// 알고리즘 태그 목록
/*
수학
구현
사칙연산
임의 정밀도 / 큰 수 연산
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A, B;
    cin >> A >> B;

    int A_length = A.length();
    int B_length = B.length();
    int max_length = A_length > B_length ? A_length : B_length;

    string A_str, B_str;

    for(int i = 0; i < max_length-A_length; i++) A_str += "0";
    for(int i = 0; i < max_length-B_length; i++) B_str += "0";
    A_str += A;
    B_str += B;

    string result;
    int status = 0;
    int index = max_length - 1;
    for(int i = 0; i < max_length; i++) {
        int temp = static_cast<int>(A_str[index - i]) + static_cast<int>(B_str[index - i]) - 96 + status;
        result = to_string(temp % 10) + result;
        status = temp / 10;
    }

    if (status == 1) result = "1" + result;

    cout << result << '\n';

    return 0;
}