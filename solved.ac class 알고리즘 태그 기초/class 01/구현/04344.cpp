// 4344(평균은 넘겠지) 문제 : https://www.acmicpc.net/problem/4344
// 알고리즘 태그 목록
/*
수학
사칙연산
*/
#include <iostream>
#include <vector>
#include <iomanip>
 
using namespace std;

// 실수 기초
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int C;
    cin >> C;

    while (C--) {
        int N;
        cin >> N;
        
        vector<int> scores(N);
        int total = 0;

        for (int i = 0; i < N; ++i) {
            cin >> scores[i];
            total += scores[i];
        }

        int average_pass = 0;

        for (int i = 0; i < N; ++i) {
            if (scores[i] * N > total) {
                average_pass++;
            }
        }

        double result = (double)average_pass / N * 100.0;

        cout << fixed << setprecision(3) << result << "%\n";
    }
 
    return 0;
}