// 1701(Cubeditor) 문제 : https://www.acmicpc.net/problem/1701
// 알고리즘 태그 목록
/*
문자열
kmp
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// KMP의 실패 함수(Failure Function)를 구하는 함수
int get_max_pi(const string& p) {
    int m = p.length();
    int j = 0;
    int max_val = 0;
    vector<int> pi(m, 0);

    for (int i = 1; i < m; i++) {
        // 일치하지 않으면 일치했던 이전 지점으로 되돌아감
        while (j > 0 && p[i] != p[j]) {
            j = pi[j - 1];
        }
        // 문자가 일치하면 길이를 늘림
        if (p[i] == p[j]) {
            pi[i] = ++j;
            // 현재 접미사에서 찾은 최대 중복 길이 갱신
            max_val = max(max_val, pi[i]);
        }
    }
    return max_val;
}

int main() {
    // 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    int n = s.length();
    int result = 0;

    // 모든 접미사에 대해 실패 함수를 실행
    // O(N^2)의 복잡도를 가짐 (N=5000 이므로 약 25,000,000 연산)
    for (int i = 0; i < n; i++) {
        // i번째 인덱스부터 시작하는 접미사 추출
        string suffix = s.substr(i);
        
        // 해당 접미사 내에서 가장 긴 '접두사==접미사' 길이를 구함
        result = max(result, get_max_pi(suffix));
    }

    cout << result << "\n";

    return 0;
}