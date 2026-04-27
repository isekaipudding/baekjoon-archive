// 25501(재귀의 귀재) 문제 : https://www.acmicpc.net/problem/25501
// 알고리즘 태그 목록
/*
구현
문자열
재귀
*/
#include <iostream>
#include <string>

using namespace std;

// s : 문자열, l : 왼쪽 인덱스, r : 오른쪽 인덱스, count : 호출 횟수 카운트
int recursion(const string& s, int l, int r, int& count) {
    count++; // 함수가 호출될 때마다 카운트 증가
    
    // 기저 사례 1 : 모든 문자를 확인했을 때
    if (l >= r) return 1;
    // 기저 사례 2 : 양 끝 문자가 다를 때
    else if (s[l] != s[r]) return 0;
    // 재귀 단계 : 범위를 좁혀서 다시 확인
    else return recursion(s, l + 1, r - 1, count);
}

int isPalindrome(const string& s, int& count) {
    return recursion(s, 0, s.length() - 1, count);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;

        int count = 0;
        int result = isPalindrome(s, count);

        // 결과와 호출 횟수 출력
        cout << result << " " << count << "\n";
    }

    return 0;
}