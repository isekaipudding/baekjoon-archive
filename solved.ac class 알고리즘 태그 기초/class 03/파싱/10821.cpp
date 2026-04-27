// 10821(정수의 개수) 문제 : https://www.acmicpc.net/problem/10821
// 알고리즘 태그 목록
/*
문자열
파싱
*/
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    // 공백이 없는 문자열이므로 cin >> s; 로 충분합니다.
    cin >> s;

    stringstream ss(s);
    string buffer;
    int count = 0;

    /*
    ss (입력 스트림) : 어디서 데이터를 가져올 것인가? (여기서는 문자열이 담긴 stringstream 객체)
    buffer (저장 공간) : 읽어온 문자열을 어디에 담아둘 것인가? (보통 string 타입의 변수)
    ',' (구분자/Delimiter) : 어디까지 읽고 멈출 것인가? (여기서는 콤마)
    */
    // 콤마(',')를 기준으로 문자열을 잘라 buffer에 담습니다.
    while (getline(ss, buffer, ',')) {
        count++;
    }

    cout << count << "\n";

    return 0;
}